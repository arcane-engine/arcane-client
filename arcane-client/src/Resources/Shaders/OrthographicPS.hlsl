// ReSharper disable All

#include "Includes.hlsli"

Texture2D albedoTexture : register(TEXTURE_BINDING_SLOT_ALBEDO);

SamplerState Sampler : register(SAMPLER_BINDING_SLOT);

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