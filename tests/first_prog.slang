/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
/*
 * All code in this shader should compile even if the program is utter rubbish.
 */
float ann_var_0 = 1, var_0, var_1;

const float var2_0 = 32, var2_1 = 64;

register(4)
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

register(vs, 0) register(ps, 1)
cbuffer const_buf_1 {
    noperspective float4 some_const_thing_1 = float4(1,0,0,1); // TODO default assignments
    row_major float4x4 some_const_thing_2;
    float4 some_const_thing_0, some_const_thing_3;
};

shared const
struct TestStruct {
    row_major float4x4 mem11;
    centroid float4 mem12;
    float4 mem13;
} const_input_0;

struct VSInput {
    semantic(POSITION) float3 position;
    semantic(TEXCOORD0) float4 colour;
    semantic(TEXCOORD1) float2 uv;
};

register(30)
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
float4 main_vs(semantic(POSITION) float4 in_pos, semantic(TEXCOORD1) float4 in_tc);

// function bodies
semantic(SV_POSITION)
float4 main_vs(semantic(POSITION) float4 in_pos, semantic(TEXCOORD1) float4 in_tc) {
    float4 worldPos;
    worldPos = float4(in_pos, 1);
    ++in_pos;
    return worldPos * 
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
