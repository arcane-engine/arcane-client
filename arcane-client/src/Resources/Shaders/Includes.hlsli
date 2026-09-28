// ReSharper disable All

#define TRANSFORM_CAMERA_BINDING_SLOT  b0
#define TRANSFORM_OBJECT_BINDING_SLOT  b1

#define TEXTURE_BINDING_SLOT_ALBEDO    t0

#define SAMPLER_BINDING_SLOT           s0

cbuffer CameraBuffer : register(TRANSFORM_CAMERA_BINDING_SLOT)
{
    matrix ViewMatrix;
    matrix ProjectionMatrix;
};

cbuffer ObjectBuffer : register(TRANSFORM_OBJECT_BINDING_SLOT)
{
    matrix WorldMatrix;
    matrix WorldViewProjectionMatrix;
};