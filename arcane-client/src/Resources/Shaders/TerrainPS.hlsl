// ReSharper disable All

#include "Registers.hlsli"

Texture2D terrainWeightTexture : register(TEX_REGISTER_TERRAIN_WEIGHT);
Texture2D terrainBaseTexture : register(TEX_REGISTER_TERRAIN_BASE);

SamplerState Sampler : register(SMP_REGISTER_MAIN);

struct PSInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
    float2 uv1 : TEXCOORD1;
    float3 worldPosition : POSITION0;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 t1 = terrainWeightTexture.Sample(Sampler, input.uv0);
    float4 t2 = terrainBaseTexture.Sample(Sampler, input.uv1);

    float4 blendedColor = (t1 + t2) / 2;

    return float4(blendedColor.rgb, 1.0f);
}
