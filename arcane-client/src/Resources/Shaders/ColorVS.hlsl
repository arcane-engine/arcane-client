struct VSInput
{
    float3 position : POSITION;
};

struct VSResult
{
    float4 position : SV_POSITION;
};

VSResult main(VSInput input)
{
    VSResult result;

    result.position = float4(input.position, 1.0f);

    return result;
}
