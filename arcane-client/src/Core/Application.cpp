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
#include "Graphics/RenderResource/VertexBuffer.h"
#include "Graphics/RenderResource/Data/CameraTransformBuffer.h"
#include "Graphics/RenderResource/Data/ObjectTransformBuffer.h"

namespace Core
{
    Application::Application(const int width, const int height) :
        _window(width, height),
        _device(_window.GetDevice()),
        _shaderLibrary(_device),
        _camera(width, height)
    {
        _renderPipeline.Build(_device, _shaderLibrary);

        std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        std::vector<Graphics::Vertex> vertexBuffer = {
            {  0.0f,  1.0f,  5.0f,  0.0f,  0.0f },
            {  1.0f, -1.0f,  5.0f,  0.0f,  0.0f },
            { -1.0f, -1.0f,  5.0f,  0.0f,  0.0f }
        };

        std::vector<unsigned int> indexBuffer = {
            0, 1, 2
        };

        _camera.Update();
        auto cameraTransformBuffer = Graphics::CameraTransformBuffer(
            DirectX::XMMatrixTranspose(_camera.GetViewMatrix()),
            DirectX::XMMatrixTranspose(_camera.GetProjectionMatrix())
        );
        auto objectTransformBuffer = Graphics::ObjectTransformBuffer(
            DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity()),
            DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity() * _camera.GetViewMatrix() * _camera.GetProjectionMatrix())
        );

        _cameraObject.Add(std::make_unique<Graphics::ConstantBuffer<Graphics::CameraTransformBuffer>>(_device, cameraTransformBuffer, 0));

        _object.SetIndexCount(static_cast<UINT>(indexBuffer.size()));
        _object.Add(std::make_unique<Graphics::PixelShader>(_shaderLibrary.GetPixelShader("Color")));
        _object.Add(std::make_unique<Graphics::VertexShader>(_shaderLibrary.GetVertexShader("Color")));
        _object.Add(std::make_unique<Graphics::VertexBuffer>(_device, vertexBuffer));
        _object.Add(std::make_unique<Graphics::IndexBuffer>(_device, indexBuffer));
        _object.Add(std::make_unique<Graphics::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        _object.Add(std::make_unique<Graphics::ConstantBuffer<Graphics::ObjectTransformBuffer>>(_device, objectTransformBuffer, 1));
        _object.Add(std::make_unique<Graphics::InputLayout>(_device, inputLayout, _shaderLibrary.GetVertexShaderBlob("Color")));
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
            _camera.Rotate(y, -x, 0.0f);
        }

        _camera.Update();

        auto context = Graphics::RenderContext(_camera.GetViewMatrix(), _camera.GetProjectionMatrix());

        _renderQueue.Add(_cameraObject);
        _renderQueue.Add(_object, DirectX::XMMatrixIdentity());
        
        const auto world = DirectX::XMMatrixTranslation(0.0f, 2.0f, 0.0f);
        _renderQueue.Add(_object, world);

        _renderPipeline.Execute(_device, _renderQueue, context);
    }
}
