// ReSharper disable All
#include "TransformBuffers.hlsli"

struct VSInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = mul(float4(input.position, 1.0f), worldViewProjectionMatrix);
    output.normal = normalize(mul(input.normal, (float3x3) worldMatrix));
    output.uv0 = input.uv0;

    return output;
}