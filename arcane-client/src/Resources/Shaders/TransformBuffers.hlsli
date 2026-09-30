#ifndef TRANSFORM_BUFFERS_HLSLI
#define TRANSFORM_BUFFERS_HLSLI

#include "Registers.hlsli"

cbuffer CameraBuffer : register(CB_REGISTER_CAMERA)
{
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer ObjectBuffer : register(CB_REGISTER_OBJECT)
{
    matrix worldMatrix;
    matrix worldViewProjectionMatrix;
};

#endif