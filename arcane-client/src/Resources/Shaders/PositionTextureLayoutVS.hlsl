// ReSharper disable CppInconsistentNaming

#include "VertexTypes.hlsli"

struct VSOutput
{
    float4 position : SV_Position;
};

VSOutput main(VSInput_PositionTexture input)
{
    VSOutput output;

    output.position = float4(input.position, 1.0f);

    return output;
}
