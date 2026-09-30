// ReSharper disable All

#include "Registers.hlsli"

Texture2D albedoTexture : register(TEX_REGISTER_ALBEDO);

SamplerState Sampler : register(SMP_REGISTER_MAIN);

struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv0 : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 albedoColor = albedoTexture.Sample(Sampler, input.uv0);

    return float4(albedoColor.rgb, 1.0f);
}
