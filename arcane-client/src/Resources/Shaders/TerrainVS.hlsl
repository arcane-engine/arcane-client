// ReSharper disable All

#include "ConstantBuffers.hlsli"
#include "VertexTypes.hlsli"

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
    float2 uv1 : TEXCOORD1;
    float3 worldPosition : POSITION0;
};

VSOutput main(VSInput_Terrain input)
{
    VSOutput output;

    output.position = mul(float4(input.position, 1.0f), worldViewProjectionMatrix);
    output.normal = normalize(mul(input.normal, (float3x3) worldMatrix));
    output.uv0 = input.uv0;
    output.uv1 = input.uv1;
    output.worldPosition = mul(float4(input.position, 1.0f), worldMatrix).xyz;

    return output;
}