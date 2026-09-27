#include "Core/Application.h"

#include "Graphics/RenderObject.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderResource/InputLayout.h"
#include "Graphics/RenderResource/PixelShader.h"
#include "Graphics/RenderResource/Topology.h"
#include "Graphics/RenderResource/VertexShader.h"
#include "Graphics/RenderResource/IndexBuffer.h"
#include "Graphics/RenderResource/VertexBuffer.h"

namespace Core
{
    Application::Application(const int width, const int height) :
        _window(width, height),
        _device(_window.GetDevice()),
        _shaderLibrary(_device)
    {
        _renderPipeline.Build(_device);

        const std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        const std::vector<Graphics::Vertex> vertexBuffer = {
            {  0.0f,  0.5f,  0.0f },
            {  0.5f, -0.5f,  0.0f },
            { -0.5f, -0.5f,  0.0f }
        };

        const std::vector<unsigned int> indexBuffer = {
            0, 1, 2
        };

        _object.SetIndexCount(static_cast<::UINT>(indexBuffer.size()));
        _object.Add(std::make_unique<Graphics::PixelShader>(_shaderLibrary.GetPixelShader("")));
        _object.Add(std::make_unique<Graphics::VertexShader>(_shaderLibrary.GetVertexShader("")));
        _object.Add(std::make_unique<Graphics::VertexBuffer>(_device, vertexBuffer));
        _object.Add(std::make_unique<Graphics::IndexBuffer>(_device, indexBuffer));
        _object.Add(std::make_unique<Graphics::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        _object.Add(std::make_unique<Graphics::InputLayout>(_device, inputLayout, _shaderLibrary.GetVertexShaderBlob("")));
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

        _renderQueue.Add(_object, DirectX::XMMatrixIdentity());

        _renderPipeline.Execute(_device, _renderQueue);
    }
}
