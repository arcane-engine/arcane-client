#pragma once

#include <vector>

#include "Core/Context/CameraContext.h"
#include "Core/Context/InputContext.h"
#include "Core/Context/ObjectContext.h"
#include "Core/Context/TimeContext.h"
#include "Graphics/RenderQueue.h"

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
        Graphics::RenderQueue GeometryRenderQueue;
        Graphics::RenderQueue UserInterfaceRenderQueue;
    };
}
