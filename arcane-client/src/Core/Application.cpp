#include "Core/Application.h"

#include "Graphics/RenderContext.h"
#include "Graphics/RenderObject.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderResource/ConstantBuffer.h"
#include "Graphics/RenderResource/InputLayout.h"
#include "Graphics/RenderResource/PixelShader.h"
#include "Graphics/RenderResource/Topology.h"
#include "Graphics/RenderResource/VertexShader.h"
#include "Graphics/RenderResource/IndexBuffer.h"
#include "Graphics/RenderResource/Sampler.h"
#include "Graphics/RenderResource/Texture.h"
#include "Graphics/RenderResource/VertexBuffer.h"
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

        std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        std::vector<Graphics::Vertex> vertexBuffer = {
            {  0.0f,  1.0f,  5.0f,  0.5f, 1.0f },
            {  1.0f, -1.0f,  5.0f,  1.0f, 0.0f },
            { -1.0f, -1.0f,  5.0f,  0.0f, 0.0f }
        };

        std::vector<unsigned int> indexBuffer = {
            0, 1, 2
        };

        _cameraObject.Add(std::make_unique<Graphics::ConstantBuffer<Graphics::CameraTransformBuffer>>(_device, 0));

        _object.SetIndexCount(static_cast<UINT>(indexBuffer.size()));
        _object.Add(std::make_unique<Graphics::PixelShader>(_shaderLibrary.GetPixelShader("Texture")));
        _object.Add(std::make_unique<Graphics::VertexShader>(_shaderLibrary.GetVertexShader("Texture")));
        _object.Add(std::make_unique<Graphics::VertexBuffer>(_device, vertexBuffer));
        _object.Add(std::make_unique<Graphics::IndexBuffer>(_device, indexBuffer));
        _object.Add(std::make_unique<Graphics::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        _object.Add(std::make_unique<Graphics::Sampler>(_device, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP));
        _object.Add(std::make_unique<Graphics::Texture>(_textureLibrary.GetTexture("Texture"), Resources::TextureBindingSlot::Albedo));
        _object.Add(std::make_unique<Graphics::ConstantBuffer<Graphics::ObjectTransformBuffer>>(_device, 1));
        _object.Add(std::make_unique<Graphics::InputLayout>(_device, inputLayout, _shaderLibrary.GetVertexShaderBlob("Texture")));
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
