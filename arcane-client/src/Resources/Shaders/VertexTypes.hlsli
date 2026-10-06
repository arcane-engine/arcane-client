// ReSharper disable CppInconsistentNaming

struct VSInput_PositionTexture
{
    float3 position : POSITION;
    float2 uv0 : TEXCOORD0;
};

struct VSInput_PositionNormalTexture
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
};

struct VSInput_PositionNormalTexture_Instanced
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv0 : TEXCOORD0;
    float4 instanceMatrixRow0 : INSTANCE_MATRIX0;
    float4 instanceMatrixRow1 : INSTANCE_MATRIX1;
    float4 instanceMatrixRow2 : INSTANCE_MATRIX2;
    float4 instanceMatrixRow3 : INSTANCE_MATRIX3;
};