#pragma once

#include "Graphics/RenderObject.h"
#include "Graphics/RenderQueue.h"

namespace Resources
{
    class ResourceManager;
}

namespace Graphics
{
    class RenderSystem;
}

namespace UserInterface
{
    class UserInterfaceSystem
    {
    private:
        enum class Alignment {
            TopLeft,
            Center
        };

    public:
        UserInterfaceSystem(Graphics::RenderSystem& renderSystem, Resources::ResourceManager& resourceManager, int width, int height);

        void SetResolution(int width, int height) noexcept;

        [[nodiscard]] Graphics::RenderQueue BuildRenderQueue() const;

    private:
        DirectX::XMMATRIX CalculateTransform(float pixelX, float pixelY, float pixelWidth, float pixelHeight, Alignment alignment) const;

        int _width;
        int _height;

        Graphics::RenderObject _userInterface;
    };
}
