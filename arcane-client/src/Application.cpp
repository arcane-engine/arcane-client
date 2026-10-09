#include "Application.h"

#include <format>

#include "Graphics/RenderContext.h"
#include "Graphics/RenderObject.h"
#include "Graphics/RenderObjectBuilder.h"
#include "Graphics/RenderResource/Data/CameraTransformBuffer.h"
#include "Graphics/RenderResource/Data/LightBuffer.h"
#include "Graphics/RenderResource/Data/ObjectTransformBuffer.h"
#include "Network/Protocol/PacketBuilder.h"
#include "Network/Protocol/Packets/ClientInputPacket.h"
#include "Network/Protocol/Packets/ClientPacket.h"

Application::Application(const int width, const int height) :
    _window(width, height),
    _device(_window.GetWindowHandle(), width, height),
    _camera(width, height),
    _shaderLibrary(_device),
    _textureLibrary(_device),
    _samplerLibrary(_device),
    _depthStencilStateLibrary(_device),
    _inputLayoutLibrary(_device, _shaderLibrary)
{
    _networkWorker.Start();
    _renderPipeline.Build(_device, _shaderLibrary, _samplerLibrary, _depthStencilStateLibrary, _inputLayoutLibrary);

    _cameraObject = Graphics::RenderObjectBuilder(_device)
        .WithConstantBuffer<Graphics::CameraTransformBuffer>(0)
        .Build();

    const auto grid = _meshLibrary.GetMesh("Grid");
    const auto cube = _meshLibrary.GetMesh("Cube");
    const auto material = _materialLibrary.GetMaterial("Default");

    _object1 = Graphics::RenderObjectBuilder(_device)
        .WithVertexShader(_shaderLibrary.GetVertexShader(material.Shaders.VertexShader))
        .WithPixelShader(_shaderLibrary.GetPixelShader(material.Shaders.PixelShader))
        .WithInputLayout(_inputLayoutLibrary.GetInputLayout(Resources::InputLayoutType::PositionNormalTexture))
        .WithDepthStencilState(_depthStencilStateLibrary.GetDepthStencilState(Resources::DepthStencilType::ReadWrite))
        .WithVertexBuffer(grid.GetVertices())
        .WithIndexBuffer(grid.GetIndices())
        .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        .WithSampler(_samplerLibrary.GetSampler(Resources::SamplerType::LinearWrap), 0)
        .WithTexture(_textureLibrary.GetTexture(material.Textures.Albedo), Resources::TextureBindingSlot::Albedo)
        .WithConstantBuffer<Graphics::ObjectTransformBuffer>(1)
        .WithConstantBuffer<Graphics::LightBuffer>(2, false, true)
        .Build();

    _object2 = Graphics::RenderObjectBuilder(_device)
        .WithVertexShader(_shaderLibrary.GetVertexShader(material.Shaders.VertexShader, true))
        .WithPixelShader(_shaderLibrary.GetPixelShader(material.Shaders.PixelShader))
        .WithInputLayout(_inputLayoutLibrary.GetInputLayout(Resources::InputLayoutType::PositionNormalTextureInstanced))
        .WithDepthStencilState(_depthStencilStateLibrary.GetDepthStencilState(Resources::DepthStencilType::ReadWrite))
        .WithVertexBuffer(cube.GetVertices())
        .WithIndexBuffer(cube.GetIndices())
        .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        .WithSampler(_samplerLibrary.GetSampler(Resources::SamplerType::LinearWrap), 0)
        .WithTexture(_textureLibrary.GetTexture(material.Textures.Albedo), Resources::TextureBindingSlot::Albedo)
        .WithInstanceVertexBuffer(1)
        .WithConstantBuffer<Graphics::LightBuffer>(2, false, true)
        .Build();
}

int Application::Run()
{
    while (true)
    {
        if (const auto exitCode = _window.ProcessMessages())
        {
            _networkWorker.Stop();
            return static_cast<int>(*exitCode);
        }

        Update();
    }
}

void Application::Update()
{
    _renderQueue.Clear();
    _timer.Update();

    SetWindowTextW(_window.GetWindowHandle(), std::wstring(std::format(L"FPS: {:.1f}", 1.0f / _timer.GetSmoothDelta())).c_str());

    while (const auto event = _window.GetMouse().ReadRawEvent())
    {
        const auto x = _window.GetMouse().GetSmoothDelta(static_cast<float>(event->X));
        const auto y = _window.GetMouse().GetSmoothDelta(static_cast<float>(event->Y));

        _camera.Rotate(-y, x, 0.0f);
    }

    if (_window.GetKeyboard().IsKeyPressed(VK_F11))
    {
        ToggleFullscreen();
    }

    if (_window.GetKeyboard().IsKeyPressed('W'))
    {
        std::uint8_t buffer[256]{};

        const auto size = Network::PacketBuilder(buffer, Network::ClientPacket{ Network::ClientInputPacket{ true, false, false, false } }).Build();

        std::vector data(buffer, buffer + size);

        _networkWorker.GetSendQueue().Push(std::move(data));
    }

    _camera.Update();

    auto context = Graphics::RenderContext(_camera.GetViewMatrix(), _camera.GetProjectionMatrix());
    context.Lights = {
        { { -8.0f, 4.0f, -8.0f, 1.0f }, { 1.0f, 0.8f, 0.6f, 1.0f } },
        { {  8.0f, 4.0f, -8.0f, 1.0f }, { 0.6f, 0.8f, 1.0f, 1.0f } },
        { { -8.0f, 4.0f,  8.0f, 1.0f }, { 1.0f, 0.6f, 0.6f, 1.0f } },
        { {  8.0f, 4.0f,  8.0f, 1.0f }, { 0.6f, 1.0f, 0.6f, 1.0f } }
    };

    _renderQueue.Add(_cameraObject);

    std::vector<DirectX::XMMATRIX> instanceMatrices;

    _renderQueue.Add(_object1, DirectX::XMMatrixTranslation(-20.0f, -3.0f, -20.0f));

    for (auto x = -5; x <= 5; x++)
    {
        for (auto z = -5; z <= 5; z++)
        {
            instanceMatrices.push_back(DirectX::XMMatrixScaling(0.5, 0.5, 0.5) * DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(x), 2, static_cast<float>(z)) * DirectX::XMMatrixTranslation(static_cast<float>(x * 4) - 20, 3.0f, static_cast<float>(z * 4) - 20));
        }
    }

    _renderQueue.Add(_object2, instanceMatrices);

    _renderPipeline.Execute(_device, _renderQueue, context);
}

void Application::ToggleFullscreen()
{
    _window.ToggleFullscreen();

    const auto width = _window.GetWidth();
    const auto height = _window.GetHeight();

    _device.SetResolution(width, height);
    _camera.SetResolution(width, height);

    _renderPipeline.Build(_device, _shaderLibrary, _samplerLibrary, _depthStencilStateLibrary, _inputLayoutLibrary);
}
