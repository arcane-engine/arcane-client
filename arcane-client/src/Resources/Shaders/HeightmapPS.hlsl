// ReSharper disable All

#include "Registers.hlsli"
#include "ConstantBuffers.hlsli"

Texture2D heightmapTexture : register(TEX_REGISTER_HEIGHTMAP);

SamplerState Sampler : register(SMP_REGISTER_MAIN);

struct PSInput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION0;
};

float4 main(PSInput input) : SV_TARGET
{
    float terrainSize = 512.0f;

    float2 uv = (input.worldPosition.xz / terrainSize) + 0.5f;

    float heightValue = heightmapTexture.Sample(Sampler, uv).r;

    return float4(heightValue, heightValue, heightValue, 1.0f);
}
