// ReSharper disable All

#include "Includes.hlsli"

struct VSInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VSResult
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VSResult main(VSInput input)
{
    VSResult result;

    result.position = mul(float4(input.position, 1.0f), WorldViewProjectionMatrix);
    result.uv = input.uv;

    return result;
}
