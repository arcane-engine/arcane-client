// ReSharper disable All

#include "Registers.hlsli"

Texture2D renderTargerTexture : register(TEX_REGISTER_RENDER_TARGET);
Texture2D depthStencilTexture : register(TEX_REGISTER_DEPTH_STENCIL);

SamplerState Sampler : register(SMP_REGISTER_MAIN);

struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv0 : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 renderTargerColor = renderTargerTexture.Sample(Sampler, input.uv0);
    float4 depthStencilColor = depthStencilTexture.Sample(Sampler, input.uv0);

    //return float4(depthStencilColor.r, depthStencilColor.r, depthStencilColor.r, 1.0f);

    return float4(renderTargerColor.rgb, 1.0f);
}
