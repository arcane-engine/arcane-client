// ReSharper disable All

#include "Registers.hlsli"
#include "VertexTypes.hlsli"

cbuffer ObjectTransformBuffer : register(CB_REGISTER_OBJECT_TRANSFORM)
{
    matrix worldMatrix;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 uv0 : TEXCOORD0;
};

VSOutput main(VSInput_PositionTexture input)
{
    VSOutput output;

    output.position = mul(float4(input.position, 1.0f), worldMatrix);
    output.uv0 = input.uv0;

    return output;
}
