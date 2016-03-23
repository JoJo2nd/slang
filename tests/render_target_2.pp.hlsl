#line 1 "C:/Users/James/dev/mcpp-2.7.2/bin/render_target_2.sdr"
#line 2 "C:/Users/James/dev/mcpp-2.7.2/bin/render_target_2.sdr"
#line 1 "ViewportConstants.hlsl.h"
#line 8 "ViewportConstants.hlsl.h"
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
#line 3 "C:/Users/James/dev/mcpp-2.7.2/bin/render_target_2.sdr"
#line 1 "InstanceConstants.hlsl.h"
#line 8 "InstanceConstants.hlsl.h"
cbuffer InstanceConstants {
	float4x4 world;
};
#line 4 "C:/Users/James/dev/mcpp-2.7.2/bin/render_target_2.sdr"

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
    PSInput ov;
    ov.colour = iv.uv.xyxy;
    float4 wp = mul(world, float4(iv.position.xyz, 1));
    ov.position.xyzw = mul(viewProjection, float4(wp.xyz, 1));
    return ov;
}

float4 main_ps( PSInput ip ) : SV_Target0 {
    return t_tex2D.Sample(tSampler, ip.colour.xy);
}
