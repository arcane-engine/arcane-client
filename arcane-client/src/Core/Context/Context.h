#pragma once

#include <vector>
#include <span>

#include "Core/Context/CameraContext.h"
#include "Core/Context/InputContext.h"
#include "Core/Context/ObjectContext.h"
#include "Core/Context/TimeContext.h"

namespace Core
{
    struct Light
    {
        DirectX::XMFLOAT4 Position;
        DirectX::XMFLOAT4 Color;
    };

    struct Context
    {
        TimeContext Time;
        InputContext Input;
        CameraContext Camera;
        ObjectContext Object;
        std::vector<Light> Lights;
        std::span<const DirectX::XMMATRIX> InstanceMatrices;
    };
}
