
float test_float_type = 0;
float2 test_float2_type;
float3 test_float3_type;
float4 test_float4_type = float4(0, 0, 0, 1);

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

struct VSInput {
    float3 position : POSITION;
    float4 colour : TEXCOORD0;
    float2 uv : TEXCOORD1;
};

struct PSInput {
    float4 position : SV_POSITION;
    float4 colour : TEXCOORD0;
};

PSInput main_vs(VSInput iv) {
    //float4 wp = float4(iv.position.x, iv.position.y, iv.position.z, 1);
    //PSInput ov;
    wp = world*float4(iv.position.xyz, 1);
    ov.position.xyzw = viewProjection*float4(wp.xyz, 1);
    ov.colour = iv.uv.xyxy;
    return ov;
}

float4 main_ps( PSInput ip ) : SV_Target0
{
    return ip.colour;
    //return texture(tSampler, t_tex2D) * ip.colour;
}