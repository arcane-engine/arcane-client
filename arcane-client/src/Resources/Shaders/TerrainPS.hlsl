// ReSharper disable All

#include "Registers.hlsli"
#include "ConstantBuffers.hlsli"

Texture2D terrainWeightTexture : register(TEX_REGISTER_TERRAIN_WEIGHT);
Texture2D terrainBaseTexture : register(TEX_REGISTER_TERRAIN_BASE);
Texture2D terrainRTexture : register(TEX_REGISTER_TERRAIN_R);

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
    float4 weightColor = terrainWeightTexture.Sample(Sampler, input.uv0);
    float4 baseColor = terrainBaseTexture.Sample(Sampler, input.uv1);
    float4 textureColor = terrainRTexture.Sample(Sampler, input.uv1);

    float4 blendedColor = lerp(baseColor, textureColor, weightColor.r);

    float3 totalLight = float3(0.4f, 0.4f, 0.6f);

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

    return float4(blendedColor.rgb * totalLight * 2.0f, 1.0f);
}
