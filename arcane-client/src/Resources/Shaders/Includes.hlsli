// ReSharper disable All

#define VS_BINDING_SLOT_TRANSFORM      b0

#define TEXTURE_BINDING_SLOT_ALBEDO    t0

#define SAMPLER_BINDING_SLOT           s0

cbuffer VSOrthographicTransformConstant : register(VS_BINDING_SLOT_TRANSFORM)
{
    matrix projection;
};