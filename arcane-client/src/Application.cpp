#include "Application.h"

#include <format>

#include "Graphics/RenderObject.h"
#include "Graphics/RenderObjectBuilder.h"
#include "Graphics/RenderResource/Data/CameraTransformBuffer.h"
#include "Graphics/RenderResource/Data/LightBuffer.h"
#include "Graphics/RenderResource/Data/ObjectTransformBuffer.h"
#include "Core/Context/Context.h"

Application::Application(const int width, const int height) :
    _window(width, height),
    _camera(width, height),
    _renderSystem(_window.GetWindowHandle(), width, height),
    _resourceManager(_renderSystem.GetDevice())
{
    _networkSystem.Start();

    _renderSystem.BuildRenderPipeline(_resourceManager);

    _cameraObject = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithConstantBuffer<Graphics::CameraTransformBuffer>(0)
        .Build();

    const auto grid = _resourceManager.GetMesh("Grid");
    const auto cube = _resourceManager.GetMesh("Cube");
    const auto material = _resourceManager.GetMaterial("Default");

    _object1 = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithVertexShader(_resourceManager.GetVertexShader("Terrain"))
        .WithPixelShader(_resourceManager.GetPixelShader("Terrain"))
        .WithInputLayout(_resourceManager.GetInputLayout(Resources::InputLayoutType::Terrain))
        .WithDepthStencilState(_resourceManager.GetDepthStencilState(Resources::DepthStencilStateType::Write))
        .WithVertexBuffer(grid.GetVertexBuffer(), grid.GetStride())
        .WithIndexBuffer(grid.GetIndexBuffer())
        .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        .WithSampler(_resourceManager.GetSampler(Resources::SamplerType::LinearWrap), 0)
        .WithTexture(_resourceManager.GetTexture(material.Textures.Albedo), Resources::TextureBindingSlot::TerrainWeight)
        .WithTexture(_resourceManager.GetTexture("Grass"), Resources::TextureBindingSlot::TerrainBase)
        .WithConstantBuffer<Graphics::ObjectTransformBuffer>(1)
        .WithConstantBuffer<Graphics::LightBuffer>(2, false, true)
        .Build();

    _object2 = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithVertexShader(_resourceManager.GetVertexShader(material.Shaders.VertexShader, true))
        .WithPixelShader(_resourceManager.GetPixelShader(material.Shaders.PixelShader))
        .WithInputLayout(_resourceManager.GetInputLayout(Resources::InputLayoutType::PositionNormalTextureInstanced))
        .WithDepthStencilState(_resourceManager.GetDepthStencilState(Resources::DepthStencilStateType::Write))
        .WithVertexBuffer(cube.GetVertexBuffer(), cube.GetStride())
        .WithIndexBuffer(cube.GetIndexBuffer())
        .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        .WithSampler(_resourceManager.GetSampler(Resources::SamplerType::LinearWrap), 0)
        .WithTexture(_resourceManager.GetTexture(material.Textures.Albedo), Resources::TextureBindingSlot::Albedo)
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
            _networkSystem.Stop();
            return static_cast<int>(*exitCode);
        }

        Update();
    }
}

void Application::Update()
{
    _renderSystem.ClearRenderQueue();

    if (_window.GetKeyboard().IsKeyPressed(VK_F11))
    {
        ToggleFullscreen();
    }

    auto context = Core::Context();
    context.Time = _timeSystem.Update();
    context.Input = _inputSystem.Update(_window);
    context.Camera = _camera.Update(context.Input.Mouse);
    _window.GetMouse().Update(context.Camera);
    _networkSystem.SendInput(context.Input);
    _networkSystem.Update();

    context.Lights = {
        { { -8.0f, 4.0f, -8.0f, 1.0f }, { 1.0f, 0.8f, 0.6f, 1.0f } },
        { {  8.0f, 4.0f, -8.0f, 1.0f }, { 0.6f, 0.8f, 1.0f, 1.0f } },
        { { -8.0f, 4.0f,  8.0f, 1.0f }, { 1.0f, 0.6f, 0.6f, 1.0f } },
        { {  8.0f, 4.0f,  8.0f, 1.0f }, { 0.6f, 1.0f, 0.6f, 1.0f } }
    };

    _renderSystem.GetRenderQueue().Add(_cameraObject);

    _renderSystem.GetRenderQueue().Add(_object1, DirectX::XMMatrixTranslation(-20.0f, -3.0f, -20.0f));

    std::vector<DirectX::XMMATRIX> instanceMatrices;
    for (auto x = -5; x <= 5; x++)
    {
        for (auto z = -5; z <= 5; z++)
        {
            instanceMatrices.push_back(DirectX::XMMatrixScaling(0.5, 0.5, 0.5) * DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(x), 2, static_cast<float>(z)) * DirectX::XMMatrixTranslation(static_cast<float>(x * 4) - 20, 3.0f, static_cast<float>(z * 4) - 20));
        }
    }

    _renderSystem.GetRenderQueue().Add(_object2, instanceMatrices);

    _renderSystem.ExecuteRenderPipeline(context);
}

void Application::ToggleFullscreen()
{
    _window.ToggleFullscreen();

    const auto width = _window.GetWidth();
    const auto height = _window.GetHeight();

    _renderSystem.GetDevice().SetResolution(width, height);
    _camera.SetResolution(width, height);
    _window.GetMouse().SetResolution(width, height);

    _renderSystem.BuildRenderPipeline(_resourceManager);
}
