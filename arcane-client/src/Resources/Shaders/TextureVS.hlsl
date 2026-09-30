// ReSharper disable All

#include "TransformBuffers.hlsli"

struct VSInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD0;
};

struct VSResult
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

VSResult main(VSInput input)
{
    VSResult result;

    result.position = mul(float4(input.position, 1.0f), worldViewProjectionMatrix);
    result.uv = input.uv;

    return result;
}
