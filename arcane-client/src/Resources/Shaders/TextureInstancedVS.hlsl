// ReSharper disable All

#include "ConstantBuffers.hlsli"
#include "VertexTypes.hlsli"

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
    float3 worldPosition : POSITION0;
};

VSOutput main(VSInput_PositionNormalTexture_Instanced input)
{
    VSOutput output;

    matrix worldMatrix = matrix(
        input.worldMatrixRow0,
        input.worldMatrixRow1,
        input.worldMatrixRow2,
        input.worldMatrixRow3
    );

    float4 worldPos = mul(float4(input.position, 1.0f), worldMatrix);
    
    output.position = mul(worldPos, mul(viewMatrix, projectionMatrix));
    output.normal = normalize(mul(input.normal, (float3x3) worldMatrix));
    output.uv0 = input.uv0;
    output.worldPosition = worldPos.xyz;

    return output;
}