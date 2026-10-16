// ReSharper disable All

#include "ConstantBuffers.hlsli"
#include "VertexTypes.hlsli"

Texture2D heightmapTexture : register(TEX_REGISTER_HEIGHTMAP);
SamplerState Sampler : register(SMP_REGISTER_MAIN);

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION0;
};

VSOutput main(VSInput_Heightmap input)
{
    VSOutput output;

    float3 position = input.position;
    float2 uv = (input.position.xz / 512.0f) + 0.5f;

    float height = heightmapTexture.SampleLevel(Sampler, uv, 0).r;

    position.y = height * 50.0f;

    output.position = mul(float4(position, 1.0f), worldViewProjectionMatrix);
    output.worldPosition = mul(float4(position, 1.0f), worldMatrix).xyz;

    return output;
}