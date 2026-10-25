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
    float4 renderTargetColor = renderTargerTexture.Sample(Sampler, input.uv0);
    float4 depthStencilColor = depthStencilTexture.Sample(Sampler, input.uv0);

    float3 fogColor = float3(0.55f, 0.60f, 0.68f);

    float depth = depthStencilColor.r;

    float minDepth = 0.98f;
    float maxDepth = 1.00f;

    float fogFactor = saturate((depth - minDepth) / (maxDepth - minDepth)) * 0.5f;

    float3 finalColor = lerp(renderTargetColor.rgb, fogColor, fogFactor);

    return float4(finalColor, 1.0f);
}
