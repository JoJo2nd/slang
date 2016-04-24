/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
// 01.slang

register(vs, 0) register(ps, 1) 
register(cs, 0, 1, 2) //error unexpected ','
cbufffer const_buf_1 { // error unexpected 'cbufffer'
    noperspective float4 some_const_thing_1 = float4(1,0,0,1);// error unexpected float4
    row_major float4x4 some_const_thing_2;
    float4 some_const_thing_0, some_const_thing_3;
};

cbuffer const_buf_2 {
    noperspective float4 some_const_thing_1  float4(1,0,0,1);// error unexpected float4
}

cbuffer const_buf_3 {
    /*row_major float4x4 some_const_thing_2;
    float4*/ some_const_thing_0, some_const_thing_3;
};

struct VSInput {
    semantic(42) float3 position; // error unexpected number
    semantic(TEXCOORD0) float4 colour;
    semantic(TEXCOORD1) float2 uv;
};

// function bodies
semantic(SV_POSITION)
float4 main_vs(semantic(POSITION) float4 in_pos, semantic(TEXCOORD1) float4 in_tc) {
    float4 worldPos;
    worldPos = float4(in_pos, 1);
    return worldPos;
}

semantic(SV_Target0)
float4 main_ps() {
    return float4(1, 1, 0, 1);
}

float local_min(float a, float b) {
    return a < b ? a : b;
}