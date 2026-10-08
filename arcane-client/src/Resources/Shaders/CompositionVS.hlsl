// ReSharper disable All

#include "VertexTypes.hlsli"

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 uv0 : TEXCOORD0;
};

VSOutput main(VSInput_PositionTexture input)
{
    VSOutput output;

    output.position = float4(input.position, 1.0f);
    output.uv0 = input.uv0;

    return output;
}
