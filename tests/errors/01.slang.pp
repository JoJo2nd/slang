#line 1 "C:/Users/James/dev/lang/tests/errors/01.slang"
#line 7 "C:/Users/James/dev/lang/tests/errors/01.slang"
#line 1 "C:/Users/James/dev/lang/tests/include/test_view_include.slang"
#line 7 "C:/Users/James/dev/lang/tests/include/test_view_include.slang"
register(vs, 9) register(ps, 10)
cbuffer ViewportConstants {
    float4x4 view;
    float4x4 viewInverse;
    float4x4 viewInverseTranspose;
    float4x4 projection;
    float4x4 projectionInverse;
    float4x4 viewProjection;
    float4x4 viewProjectionInverse;
    float4 viewportSize
};
#line 8 "C:/Users/James/dev/lang/tests/errors/01.slang"


register(vs, 0) register(ps, 1)
register(cs, 0, 1, 2)
cbufffer const_buf_1 {
    noperspective float4 some_const_thing_1 = float4(1,0,0,1);
    row_major float4x4 some_const_thing_2;
    float4 some_const_thing_0, some_const_thing_3;
};

cbuffer const_buf_2 {
    noperspective float4 some_const_thing_1 float4(1,0,0,1);
}

cbuffer const_buf_3 {
#line 24 "C:/Users/James/dev/lang/tests/errors/01.slang"
    some_const_thing_0, some_const_thing_3;
};

struct VSInput {
    semantic(42) float3 position;
    semantic(TEXCOORD0) float4 colour;
    semantic(TEXCOORD1) float2 uv;
};


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
