// ReSharper disable CppInconsistentNaming

#include "VertexTypes.hlsli"

struct VSOutput
{
    float4 position : SV_Position;
};

VSOutput main(VSInput_PositionNormalTexture_Instanced input)
{
    VSOutput output;

    output.position = float4(input.position, 1.0f);

    return output;
}
