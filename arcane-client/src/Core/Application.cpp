#include "Core/Application.h"

#include "Graphics/RenderContext.h"
#include "Graphics/RenderObject.h"
#include "Graphics/RenderObjectBuilder.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderResource/Data/CameraTransformBuffer.h"
#include "Graphics/RenderResource/Data/ObjectTransformBuffer.h"

namespace Core
{
    Application::Application(const int width, const int height) :
        _window(width, height),
        _device(_window.GetWindowHandle(), width, height),
        _shaderLibrary(_device),
        _textureLibrary(_device),
        _camera(width, height)
    {
        _renderPipeline.Build(_device, _shaderLibrary);

        const std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        const std::vector<Graphics::Vertex> vertexBuffer = {
            {  0.0f,  1.0f,  5.0f,  0.5f,  1.0f },
            {  1.0f, -1.0f,  5.0f,  1.0f,  0.0f },
            { -1.0f, -1.0f,  5.0f,  0.0f,  0.0f }
        };

        const std::vector<unsigned int> indexBuffer = {
            0, 1, 2
        };

        _cameraObject = Graphics::RenderObjectBuilder(_device)
            .WithConstantBuffer<Graphics::CameraTransformBuffer>(0)
            .Build();

        _object = Graphics::RenderObjectBuilder(_device, &_shaderLibrary, &_textureLibrary)
            .WithVertexShader("Texture")
            .WithPixelShader("Texture")
            .WithInputLayout(inputLayout, "Texture")
            .WithVertexBuffer(vertexBuffer)
            .WithIndexBuffer(indexBuffer)
            .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
            .WithSampler(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP)
            .WithTexture("Texture", Resources::TextureBindingSlot::Albedo)
            .WithConstantBuffer<Graphics::ObjectTransformBuffer>(1)
            .Build();
    }

    int Application::Run()
    {
        while (true)
        {
            if (const auto exitCode = _window.ProcessMessages())
            {
                return static_cast<int>(*exitCode);
            }

            Update();
        }
    }

    void Application::Update()
    {
        _renderQueue.Clear();

        while (const auto event = _window.GetMouse().ReadRawEvent())
        {
            const auto x = _window.GetMouse().GetSmoothDelta(event->GetX());
            const auto y = _window.GetMouse().GetSmoothDelta(event->GetY());
            _camera.Rotate(-y, x, 0.0f);
        }

        _camera.Update();

        auto context = Graphics::RenderContext(_camera.GetViewMatrix(), _camera.GetProjectionMatrix());

        _renderQueue.Add(_cameraObject);

        for (auto x = -20.0f; x <= 20.0f; x += 2.0f)
        {
            for (auto y = -20.0f; y <= 20.0f; y += 2.0f)
            {
                _renderQueue.Add(_object, DirectX::XMMatrixTranslation(x, y, 0.0f));
            }
        }
        

        _renderPipeline.Execute(_device, _renderQueue, context);
    }
}
