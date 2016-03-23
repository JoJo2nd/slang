
float test_float_type;
float2 test_float2_type;
float3 test_float3_type;
float4 test_float4_type;

cbuffer ViewportConstants {
    float4x4 view;
    float4x4 viewInverse;
    float4x4 viewInverseTranspose;
    float4x4 projection;
    float4x4 projectionInverse;
    float4x4 viewProjection;
    float4x4 viewProjectionInverse;
    float4 viewportSize;
};

cbuffer InstanceConstants {
    float4x4 world;
};

sampler tSampler;
texture2D t_tex2D;

struct AnotherVSInput {
    float3 position;
    float4 colour;
    float2 uv;
};

struct VSInput {
    float3 position : POSITION;
    float4 colour : TEXCOORD0;
    float2 uv : TEXCOORD1;
};

struct PSInput {
    float4 position : SV_POSITION;
    float4 colour : TEXCOORD0;
};

struct VSInput2 {
    float3 position;
    float4 colour;
    float2 uv;
};

struct PSInput2 {
    float4 position;
    float4 colour;
};

PSInput main_vs(VSInput iv) {
    PSInput ov;
    ov.colour = iv.uv.xyxy;
    float4 wp = float4(iv.position.x, iv.position.y, iv.position.z, 1);
    ov.position.xyz = wp.xyz;
    ov.position.w = 1;
    return ov;
}

float4 main_ps( PSInput ip ) : SV_Target0
{
    return ip.colour;
}