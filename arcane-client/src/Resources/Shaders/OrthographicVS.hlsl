// ReSharper disable All

struct VSInput
{
    float3 position : POSITION;
    float2 uv0 : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 uv0 : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = float4(input.position, 1.0f);
    output.uv0 = input.uv0;

    return output;
}
