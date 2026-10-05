// ReSharper disable All

#include "ConstantBuffers.hlsli"

struct VSInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
    float4 instanceMatrixRow0 : INSTANCE_MATRIX0;
    float4 instanceMatrixRow1 : INSTANCE_MATRIX1;
    float4 instanceMatrixRow2 : INSTANCE_MATRIX2;
    float4 instanceMatrixRow3 : INSTANCE_MATRIX3;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
    float3 worldPosition : POSITION0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    matrix instanceWorld = matrix(
        input.instanceMatrixRow0,
        input.instanceMatrixRow1,
        input.instanceMatrixRow2,
        input.instanceMatrixRow3
    );

    float4 worldPos = mul(float4(input.position, 1.0f), instanceWorld);
    
    output.position = mul(worldPos, mul(viewMatrix, projectionMatrix));
    output.normal = normalize(mul(input.normal, (float3x3) instanceWorld));
    output.uv0 = input.uv0;
    output.worldPosition = worldPos.xyz;

    return output;
}