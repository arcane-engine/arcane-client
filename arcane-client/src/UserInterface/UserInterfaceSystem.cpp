#include "UserInterface/UserInterfaceSystem.h"

#include "Graphics/RenderObjectBuilder.h"
#include "Graphics/RenderSystem.h"
#include "Graphics/Vertex.h"
#include "Resources/ResourceManager.h"

namespace UserInterface
{
    UserInterfaceSystem::UserInterfaceSystem(Graphics::RenderSystem& renderSystem, Resources::ResourceManager& resourceManager,  const int width, const int height)
        : _width(width), _height(height)
    {
        const std::vector<Graphics::UserInterfaceVertex> vertexBuffer =
        {
            { -1.0f,  1.0f, 0.0f,  0.0f,  0.0f },
            {  1.0f,  1.0f, 0.0f,  1.0f,  0.0f },
            { -1.0f, -1.0f, 0.0f,  0.0f,  1.0f },
            {  1.0f, -1.0f, 0.0f,  1.0f,  1.0f }
        };

        const unsigned int indexBuffer[] =
        {
            0, 1, 2,
            2, 1, 3
        };

        _userInterface = Graphics::RenderObjectBuilder(renderSystem.GetDevice())
            .WithVertexShader(resourceManager.GetVertexShader("UserInterface"))
            .WithPixelShader(resourceManager.GetPixelShader("UserInterface"))
            .WithInputLayout(resourceManager.GetInputLayout(Resources::InputLayoutType::PositionTexture))
            .WithDepthStencilState(resourceManager.GetDepthStencilState(Resources::DepthStencilStateType::Disabled))
            .WithVertexBuffer(vertexBuffer)
            .WithIndexBuffer(indexBuffer)
            .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
            .WithSampler(resourceManager.GetSampler(Resources::SamplerType::LinearClamp), 1, false, true)
            .WithTexture(resourceManager.GetTexture("UserInterface"), Resources::TextureBindingSlot::Albedo, false, true)
            .WithConstantBuffer<Graphics::UserInterfaceTransformBuffer>(1, true, false)
            .WithBlendState(resourceManager.GetBlendState(Resources::BlendStateType::Alpha))
            .Build();
    }

    void UserInterfaceSystem::SetResolution(const int width, const int height) noexcept
    {
        _width = width;
        _height = height;
    }

    Graphics::RenderQueue UserInterfaceSystem::BuildRenderQueue() const
    {
        auto queue = Graphics::RenderQueue();

        queue.Add(_userInterface, CalculateTransform(30, 30, 100, 100, Alignment::TopLeft));

        return std::move(queue);
    }

    DirectX::XMMATRIX UserInterfaceSystem::CalculateTransform(const float pixelX, const float pixelY, const float pixelWidth, const float pixelHeight, const Alignment alignment) const
    {
        const float scaleX = pixelWidth / static_cast<float>(_width);
        const float scaleY = pixelHeight / static_cast<float>(_height);
        const auto scale = DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f);

        float ndcX = pixelX / static_cast<float>(_width) * 2.0f - 1.0f;
        float ndcY = 1.0f - (pixelY / static_cast<float>(_height)) * 2.0f;

        if (alignment == Alignment::TopLeft)
        {
            ndcX += scaleX;
            ndcY -= scaleY;
        }

        const auto translation = DirectX::XMMatrixTranslation(ndcX, ndcY, 0.0f);

        return scale * translation;
    }
}
