#include "Application.h"

#include <format>
#include <ranges>

#include "Graphics/RenderObject.h"
#include "Graphics/RenderObjectBuilder.h"
#include "Graphics/RenderResource/Data/CameraTransformBuffer.h"
#include "Graphics/RenderResource/Data/LightBuffer.h"
#include "Graphics/RenderResource/Data/ObjectTransformBuffer.h"
#include "Core/Context/Context.h"
#include "Scene/SceneObject.h"

Application::Application(const int width, const int height) :
    _window(width, height),
    _camera(width, height),
    _renderSystem(_window.GetWindowHandle(), width, height),
    _resourceManager(_renderSystem.GetDevice()),
    _sceneSystem(_resourceManager, _renderSystem),
    _userInterfaceSystem(_renderSystem, _resourceManager, width, height)
{
    _networkSystem.Start();

    _renderSystem.BuildRenderPipeline(_resourceManager);

    auto node = Scene::SceneNode();
    node.SetSceneObject(_sceneSystem.GetObject("cube"));

    _sceneSystem.AddNode(std::move(node));

    _cameraObject = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
        .WithConstantBuffer<Graphics::CameraTransformBuffer>(0, true, false)
        .Build();

    const auto& heightMap = _resourceManager.GetMesh("terrain_mesh");
    const auto& grid = _resourceManager.GetMesh("Grid");
    const auto& cube = _resourceManager.GetMesh("Cube");
    const auto& material = _resourceManager.GetMaterial("Default");

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

    _sceneSystem.AddObject("empty", Scene::SceneObject(Graphics::RenderObjectBuilder(_renderSystem.GetDevice()).Build()));

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

    _timeSystem.Update(context);
    _inputSystem.Update(_window, context);
    _camera.Update(context);
    _window.Update(context);
    _networkSystem.Update(_actorSystem, context);
    _sceneSystem.Build();

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

    for (auto& actor : _actorSystem.GetActors() | std::views::values)
    {
        actor.Update(context.Time);
        context.GeometryRenderQueue.Add(_actorObject, actor.GetWorldMatrix());
    }

    for (const auto& object : _sceneSystem.GetObjectsView())
    {
        context.GeometryRenderQueue.Add(object->GetRenderObject(), object->GetWorldMatrixInstances());
    }

    context.GeometryRenderQueue.Add(_object2, worldMatrixInstances);

    context.UserInterfaceRenderQueue = _userInterfaceSystem.BuildRenderQueue();

    _renderSystem.ExecuteRenderPipeline(context);
}

void Application::ToggleFullscreen()
{
    _window.ToggleFullscreen();

    const auto width = _window.GetWidth();
    const auto height = _window.GetHeight();

    _renderSystem.GetDevice().SetResolution(width, height);
    _userInterfaceSystem.SetResolution(width, height);
    _camera.SetResolution(width, height);
    _window.GetMouse().SetResolution(width, height);

    _renderSystem.BuildRenderPipeline(_resourceManager);
}
