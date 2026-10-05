// ReSharper disable All

#include "Registers.hlsli"
#include "ConstantBuffers.hlsli"

Texture2D albedoTexture : register(TEX_REGISTER_ALBEDO);

SamplerState Sampler : register(SMP_REGISTER_MAIN);

struct PSInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
    float3 worldPosition : POSITION0;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 albedoColor = albedoTexture.Sample(Sampler, input.uv0);
    float3 totalLight = float3(0.15f, 0.15f, 0.15f);

    [unroll]
    for (int i = 0; i < 4; ++i)
    {
        float3 direction = positions[i].xyz - input.worldPosition;
        float distance = length(direction);
        direction = normalize(direction);

        float diff = max(dot(input.normal, direction), 0.0f);

        float attenuation = 1.0f / (1.0f + 0.01f * distance + 0.02f * (distance * distance));

        totalLight += colors[i].rgb * diff * attenuation;
    }

    return float4(albedoColor.rgb * totalLight, 1.0f);
}
