/*
* Copyright 2016 James Moran. All rights reserved.
* License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
*/
/*
* Largely based on http://www.sebastiansylvan.com/post/robin-hood-hashing-should-be-your-default-hash-table-implementation/
* also http://www.sebastiansylvan.com/post/more-on-robin-hood-hashing-2/
*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const int INITIAL_SIZE = 256;
static const int LOAD_FACTOR_PERCENT = 90;

typedef struct hash_elem {
    void* value;
    uint8_t key[];
} hash_elem_t;

typedef struct hash_table {
    uint32_t (*hash_key)(const void* key);
    int (*compare_key)(const void* a, const void* b);
    void (*value_free)(void* val);

    hash_elem_t* __restrict buffer;
    uint32_t* __restrict hashes;

    int keySize;
    int num_elems;
    int capacity;
    int resize_threshold;
    uint32_t mask;
    void* instertKeyMem;
    uint8_t swapBuffer[]; // doing this makes this class not thread-safe. However, the rest of the code is not thread aware either...
} hash_table_t;

void insert_helper(hash_table_t* hash_tbl, uint32_t hash, void* key, void* val);

static uint32_t hash_key(hash_table_t* hash_tbl, const void* key) {
    uint32_t h = hash_tbl->hash_key(key);

    // MSB is used to indicate a deleted elem, so
    // clear it
    h &= 0x7fffffff;

    // Ensure that we never return 0 as a hash,
    // since we use 0 to indicate that the elem has never
    // been used at all.
    h |= h == 0;
    return h;
}

static int is_deleted(uint32_t hash) {
    // MSB set indicates that this hash is a "tombstone"
    return (hash >> 31) != 0;
}

static int desired_pos(const hash_table_t* hash_tbl, uint32_t hash) {
    return hash & hash_tbl->mask;
}

static int probe_distance(const hash_table_t* hash_tbl, uint32_t hash, uint32_t slot_index) {
    return (slot_index + hash_tbl->capacity - desired_pos(hash_tbl, hash)) & hash_tbl->mask;
}

static uint32_t elem_hash(const hash_table_t* hash_tbl, int ix) {
    return hash_tbl->hashes[ix];
}

// alloc buffer according to currently set capacity
static void alloc(hash_table_t* hash_tbl) {
    hash_tbl->hashes = malloc(sizeof(uint32_t)*hash_tbl->capacity);
    hash_tbl->buffer = malloc((sizeof(hash_elem_t)+(hash_tbl->keySize))*hash_tbl->capacity);

    // flag all elems as free
    for (int i = 0; i < hash_tbl->capacity; ++i) {
        hash_tbl->hashes[i] = 0;
    }

    hash_tbl->resize_threshold = (hash_tbl->capacity * LOAD_FACTOR_PERCENT) / 100;
    hash_tbl->mask = hash_tbl->capacity - 1;
}

static void rehash(hash_table_t* hash_tbl) {
    hash_elem_t* old_elems = hash_tbl->buffer;
    int old_capacity = hash_tbl->capacity;
    uint32_t* old_hashes = hash_tbl->hashes;
    hash_tbl->capacity *= 2;
    alloc(hash_tbl);

    // now copy over old elems
    for (int i = 0; i < old_capacity; ++i) {
        hash_elem_t* e = old_elems+i;
        uint32_t hash = old_hashes[i];
        if (hash != 0 && !is_deleted(hash)) {
            insert_helper(hash_tbl, hash, &e->key, e->value);
        }
    }

    free(old_elems);
    free(old_hashes);
}

static void construct(hash_table_t* hash_tbl, int ix, uint32_t hash, const void* key, void* val) {
    hash_tbl->buffer[ix].value = val;
    memcpy(hash_tbl->buffer[ix].key, key, hash_tbl->keySize);
    hash_tbl->hashes[ix] = hash;
}

static void insert_helper(hash_table_t* hash_tbl, uint32_t hash, void* key, void* val) {
    int key_size = hash_tbl->keySize;
    int pos = desired_pos(hash_tbl, hash);
    int dist = 0;
    for (;;) {
        if (elem_hash(hash_tbl, pos) == 0) {
            construct(hash_tbl, pos, hash, key, val);
            return;
        }

        // If the existing elem has probed less than us, then swap places with existing
        // elem, and keep going to find another slot for that elem.
        int existing_elem_probe_dist = probe_distance(hash_tbl, elem_hash(hash_tbl, pos), pos);
        if (existing_elem_probe_dist < dist) {
            if (is_deleted(elem_hash(hash_tbl, pos))) {
                construct(hash_tbl, pos, hash, key, val);
                return;
            }

            uint32_t th = hash;
            hash = hash_tbl->hashes[pos];
            hash_tbl->hashes[pos] = th;
            
            memcpy(hash_tbl->swapBuffer, key, key_size);
            memcpy(key, hash_tbl->buffer[pos].value, key_size);
            memcpy(hash_tbl->buffer[pos].value, hash_tbl->swapBuffer, key_size);
            
            void* tv = val;
            val = hash_tbl->buffer[pos].value;
            hash_tbl->buffer[pos].value = tv;

            dist = existing_elem_probe_dist;
        }

        pos = (pos + 1) & hash_tbl->mask;
        ++dist;
    }
}

static int lookup_index(hash_table_t* hash_tbl, const void* key) {
    const uint32_t hash = hash_key(hash_tbl, key);
    int pos = desired_pos(hash_tbl, hash);
    int dist = 0;
    for (;;)
    {
        uint32_t element_hash = elem_hash(hash_tbl, pos);
        if (element_hash == 0)
            return -1;
        else if (dist > probe_distance(hash_tbl, element_hash, pos))
            return -1;
        else if (element_hash == hash && hash_tbl->compare_key(&hash_tbl->buffer[pos].key, key) == 0)
            return pos;

        pos = (pos + 1) & hash_tbl->mask;
        ++dist;
    }
}

// public interface
hash_table_t* hash_table_init(int key_size, uint32_t(*in_hash_key)(const void*), int(*in_compare_key)(const void*, const void*), void (*in_value_free)(void* val)) {
    //: buffer(nullptr), num_elems(0), capacity(INITIAL_SIZE)
    size_t required_size = sizeof(hash_table_t) + (key_size*2);
    hash_table_t* hash_tbl = malloc(required_size);
    memset(hash_tbl, 0, required_size);
    hash_tbl->hash_key = in_hash_key;
    hash_tbl->compare_key = in_compare_key;
    hash_tbl->value_free = in_value_free;
    hash_tbl->capacity = INITIAL_SIZE;
    hash_tbl->instertKeyMem = hash_tbl->swapBuffer+key_size;
    hash_tbl->keySize = key_size;
    alloc(hash_tbl);
    return hash_tbl;
}

void hash_table_insert(hash_table_t* hash_tbl, const void* key, void* val) {
    if (++hash_tbl->num_elems >= hash_tbl->resize_threshold) {
        rehash(hash_tbl);
    }
    memcpy(hash_tbl->instertKeyMem, key, hash_tbl->keySize);
    insert_helper(hash_tbl, hash_key(hash_tbl, hash_tbl->instertKeyMem), hash_tbl->instertKeyMem, val);
}

void hash_table_destroy(hash_table_t* hash_tbl) {
    for (int i = 0; i < hash_tbl->capacity; ++i) {
        if (elem_hash(hash_tbl, i) != 0) {
            if (hash_tbl->value_free) {
                hash_tbl->value_free(hash_tbl->buffer[i].value);
            }
        }
    }
    free(hash_tbl->buffer);
    free(hash_tbl->hashes);
}

void* hash_table_find(hash_table_t* hash_tbl, const void* key) {
    const int ix = lookup_index(hash_tbl, key);
    return ix != -1 ? hash_tbl->buffer[ix].value : NULL;
}

int hash_table_erase(hash_table_t* hash_tbl, const void* key) {
    const uint32_t hash = hash_key(hash_tbl, key);
    const int ix = lookup_index(hash_tbl, key);

    if (ix == -1) return 0;

    if (hash_tbl->value_free) {
        hash_tbl->value_free(hash_tbl->buffer[ix].value);
    }
    hash_tbl->hashes[ix] |= 0x80000000; // mark as deleted
    --hash_tbl->num_elems;
    return 1;
}

int hash_table_size(hash_table_t* hash_tbl) {
    return hash_tbl->num_elems;
}

float average_probe_count(hash_table_t* hash_tbl) {
    float probe_total = 0;
    for (int i = 0; i < hash_tbl->capacity; ++i)
    {
        uint32_t hash = elem_hash(hash_tbl, i);
        if (hash != 0 && !is_deleted(hash))
        {
            probe_total += probe_distance(hash_tbl, hash, i);
        }
    }
    return probe_total / hash_table_size(hash_tbl) + 1.0f;
}