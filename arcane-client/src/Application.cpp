#include "Application.h"

#include <format>
#include <ranges>

#include "Graphics/RenderObject.h"
#include "Graphics/RenderObjectBuilder.h"
#include "Graphics/RenderResource/Data/CameraTransformBuffer.h"
#include "Graphics/RenderResource/Data/LightBuffer.h"
#include "Graphics/RenderResource/Data/ObjectTransformBuffer.h"
#include "Core/Context/Context.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderResource/Data/UserInterfaceTransformBuffer.h"

Application::Application(const int width, const int height) :
    _window(width, height),
    _camera(width, height),
    _renderSystem(_window.GetWindowHandle(), width, height),
    _resourceManager(_renderSystem.GetDevice())
{
    _networkSystem.Start();

    _renderSystem.BuildRenderPipeline(_resourceManager);

    _cameraObject = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithConstantBuffer<Graphics::CameraTransformBuffer>(0, true, false)
        .Build();

    const auto heightMap = _resourceManager.GetMesh("terrain_mesh");
    const auto grid = _resourceManager.GetMesh("Grid");
    const auto cube = _resourceManager.GetMesh("Cube");
    const auto material = _resourceManager.GetMaterial("Default");

    _heightmap = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithVertexShader(_resourceManager.GetVertexShader("Heightmap"))
        .WithPixelShader(_resourceManager.GetPixelShader("Heightmap"))
        .WithInputLayout(_resourceManager.GetInputLayout(Resources::InputLayoutType::Heightmap))
        .WithDepthStencilState(_resourceManager.GetDepthStencilState(Resources::DepthStencilStateType::Write))
        .WithVertexBuffer(heightMap.GetVertexBuffer(), heightMap.GetStride())
        .WithIndexBuffer(heightMap.GetIndexBuffer())
        .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        .WithSampler(_resourceManager.GetSampler(Resources::SamplerType::LinearWrap), 0, true, true)
        .WithTexture(_resourceManager.GetHeightmapTexture("Heightmap"), Resources::TextureBindingSlot::Heightmap, true, true)
        .WithConstantBuffer<Graphics::ObjectTransformBuffer>(1, true, false)
        .WithConstantBuffer<Graphics::LightBuffer>(2, false, true)
        .Build();

    _actorObject = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithVertexShader(_resourceManager.GetVertexShader(material.Shaders.VertexShader))
        .WithPixelShader(_resourceManager.GetPixelShader(material.Shaders.VertexShader))
        .WithInputLayout(_resourceManager.GetInputLayout(Resources::InputLayoutType::Terrain))
        .WithDepthStencilState(_resourceManager.GetDepthStencilState(Resources::DepthStencilStateType::Write))
        .WithVertexBuffer(cube.GetVertexBuffer(), cube.GetStride())
        .WithIndexBuffer(cube.GetIndexBuffer())
        .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        .WithSampler(_resourceManager.GetSampler(Resources::SamplerType::LinearWrap), 0, false, true)
        .WithTexture(_resourceManager.GetTexture(material.Textures.Albedo), Resources::TextureBindingSlot::Albedo, false, true)
        .WithConstantBuffer<Graphics::ObjectTransformBuffer>(1, true, false)
        .WithConstantBuffer<Graphics::LightBuffer>(2, false, true)
        .Build();

    _object1 = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithVertexShader(_resourceManager.GetVertexShader("Terrain"))
        .WithPixelShader(_resourceManager.GetPixelShader("Terrain"))
        .WithInputLayout(_resourceManager.GetInputLayout(Resources::InputLayoutType::Terrain))
        .WithDepthStencilState(_resourceManager.GetDepthStencilState(Resources::DepthStencilStateType::Write))
        .WithVertexBuffer(grid.GetVertexBuffer(), grid.GetStride())
        .WithIndexBuffer(grid.GetIndexBuffer())
        .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        .WithSampler(_resourceManager.GetSampler(Resources::SamplerType::LinearWrap), 0, false, true)
        .WithTexture(_resourceManager.GetTexture(material.Textures.Albedo), Resources::TextureBindingSlot::TerrainWeight, false, true)
        .WithTexture(_resourceManager.GetTexture("Grass"), Resources::TextureBindingSlot::TerrainBase, false, true)
        .WithConstantBuffer<Graphics::ObjectTransformBuffer>(1, true, false)
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
        .WithSampler(_resourceManager.GetSampler(Resources::SamplerType::LinearWrap), 0, false, true)
        .WithTexture(_resourceManager.GetTexture(material.Textures.Albedo), Resources::TextureBindingSlot::Albedo, false, true)
        .WithInstanceVertexBuffer(1)
        .WithConstantBuffer<Graphics::LightBuffer>(2, false, true)
        .Build();

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

    _userInterface = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithVertexShader(_resourceManager.GetVertexShader("UserInterface"))
        .WithPixelShader(_resourceManager.GetPixelShader("UserInterface"))
        .WithInputLayout(_resourceManager.GetInputLayout(Resources::InputLayoutType::PositionTexture))
        .WithDepthStencilState(_resourceManager.GetDepthStencilState(Resources::DepthStencilStateType::Disabled))
        .WithVertexBuffer(vertexBuffer)
        .WithIndexBuffer(indexBuffer)
        .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        .WithSampler(_resourceManager.GetSampler(Resources::SamplerType::LinearClamp), 1, false, true)
        .WithTexture(_resourceManager.GetTexture("UserInterface"), Resources::TextureBindingSlot::Albedo, false, true)
        .WithConstantBuffer<Graphics::UserInterfaceTransformBuffer>(1, true, false)
        .WithBlendState(_resourceManager.GetBlendState(Resources::BlendStateType::Alpha))
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
    if (_window.GetKeyboard().IsKeyPressed(VK_F11))
    {
        ToggleFullscreen();
    }

    auto context = Core::Context();
    context.Time = _timeSystem.Update();
    context.Input = _inputSystem.Update(_window);
    context.Camera = _camera.Update(context.Input);
    _window.GetMouse().Update(context.Camera);
    _networkSystem.Send(context);
    _networkSystem.Update(_actorSystem);

    context.Lights = {
        { { -8.0f, 4.0f, -8.0f, 1.0f }, { 1.0f, 0.8f, 0.6f, 1.0f } },
        { {  8.0f, 4.0f, -8.0f, 1.0f }, { 0.6f, 0.8f, 1.0f, 1.0f } },
        { { -8.0f, 4.0f,  8.0f, 1.0f }, { 1.0f, 0.6f, 0.6f, 1.0f } },
        { {  8.0f, 4.0f,  8.0f, 1.0f }, { 0.6f, 1.0f, 0.6f, 1.0f } }
    };

    context.GeometryRenderQueue.Add(_cameraObject);

    context.GeometryRenderQueue.Add(_heightmap, DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f));
    context.GeometryRenderQueue.Add(_object1, DirectX::XMMatrixTranslation(0.0f, -3.0f, 0.0f));

    std::vector<DirectX::XMMATRIX> worldMatrixInstances;
    for (auto x = -5; x <= 5; x++)
    {
        for (auto z = -5; z <= 5; z++)
        {
            const auto scale = DirectX::XMMatrixScaling(0.5, 0.5, 0.5);
            const auto rotation = DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(x), 2, static_cast<float>(z));
            const auto position = DirectX::XMMatrixTranslation(static_cast<float>(x * 4), 3.0f, static_cast<float>(z * 4));
            worldMatrixInstances.push_back(scale * rotation * position);
        }
    }

    for (const auto& actor : _actorSystem.GetActors() | std::views::values)
    {
        context.GeometryRenderQueue.Add(_actorObject, actor.GetWorldMatrix());
    }

    context.GeometryRenderQueue.Add(_object2, worldMatrixInstances);

    const auto aspectRatio = static_cast<float>(_window.GetWidth()) / static_cast<float>(_window.GetHeight());
    constexpr auto radius = 0.2f;
    const auto scale = DirectX::XMMatrixScaling(radius / aspectRatio, radius, 1.0f);
    const auto translation = DirectX::XMMatrixTranslation(-0.75f, 0.75f, 0.0f);

    context.UserInterfaceRenderQueue.Add(_userInterface, scale * translation);

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
