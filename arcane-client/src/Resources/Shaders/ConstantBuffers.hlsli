// ReSharper disable CppInconsistentNaming

#ifndef CONSTANT_BUFFERS_HLSLI
#define CONSTANT_BUFFERS_HLSLI

#include "Registers.hlsli"

cbuffer CameraTransformBuffer : register(CB_REGISTER_CAMERA_TRANSFORM)
{
    matrix viewMatrix;
    matrix projectionMatrix;
}

cbuffer ObjectTransformBuffer : register(CB_REGISTER_OBJECT_TRANSFORM)
{
    matrix worldMatrix;
    matrix worldViewProjectionMatrix;
}

cbuffer LightBuffer : register(CB_REGISTER_LIGHT)
{
    float4 positions[4];
    float4 colors[4];
}

#endif
