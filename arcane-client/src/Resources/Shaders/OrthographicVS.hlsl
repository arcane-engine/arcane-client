// ReSharper disable All

#include "Includes.hlsli"

struct VSInput
{
    float3 position : POSITION;
    float2 uv0 : TEXCOORD0;
};

struct VSResult
{
    float4 position : SV_POSITION;
    float2 uv0 : TEXCOORD0;
};

VSResult main(VSInput input)
{
    VSResult result;

    result.position = float4(input.position, 1.0f);
    result.uv0 = input.uv0;

    return result;
}