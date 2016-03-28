//shared const float4 global_var_2 : register(c2);
//error X3000: syntax error: unexpected integer constant
//                                 : register(3);
//  error X3091: packoffset is only allowed in a constant buffer
//                                 : packoffset(c0.x);

float ann_var_0 = 1, var_0, var_1;

const float var2_0 = 32, var2_1 = 64;

register(c4)
const float var3_0;

static
float4 ann_var_1 = { 1, 2, 3, 4 };

shared noperspective
float3 ann_var_2 = float3(1, 2, 3);

noperspective shared
float3 ann_var_3 = float3(1, 2, 3);

float4 ann_var_4[16];

float4 ann_var_5[var2_0];

float4 ann_var_6[] = {
    float4(0, 0, 0,1), 
    float4(0, 0, 0,1), 
    float4(0, 0, 0,1), 
    float4(0, 0, 0,1), 
};

register(vs, c0) register(ps, c1)
cbuffer const_buf_1 {
    float4 some_const_thing_1;// = float4(1,0,0,1); TODO default assignments
    float4x4 some_const_thing_2;
    float4 some_const_thing_0; // semantics are syntactically valid on cbuffers is seems but will not appear in the input signature!
};

// following is valid.
shared const
struct TestStruct {
    row_major float4x4 mem11;
    centroid float4 mem12;
    float4 mem13;
} const_input_0;

// uniform <- not valid syntax
struct VSInput {
    semantic(POSITION) float3 position;
    semantic(TEXCOORD0) float4 colour;
    semantic(TEXCOORD1) float2 uv;
};


// following is valid. Note swap of const<->uniform
register(c30)
struct { // anonymous struct
    float4 mem1;
    float4 mem2;
    float4 mem3;
    float4 mem4;
} const_input_1;

// function prototypes
float local_max_0();
float local_max(float abc, float bcd);
const float local_min(float a, float b);

semantic(SV_POSITION)
float4 main_vs(semantic(POSITION) float4 in_pos, semantic(TEXCOORD1) float4 in_tc) {
    float4 wp;
    wp = float4(in_pos, 1);
    ++in_pos;
    return wp * 
    (some_const_thing_0
    + some_const_thing_1
    + in_tc);
}

semantic(SV_Target0)
float4 main_ps() {
    return float4(1, 0, 0, 1);
}

float local_min(float a, float b) {
    return a < b ? a : b;
}
