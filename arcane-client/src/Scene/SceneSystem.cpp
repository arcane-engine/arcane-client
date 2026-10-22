#include "Scene/SceneSystem.h"

#include <ranges>

#include "Graphics/RenderObjectBuilder.h"
#include "Graphics/RenderSystem.h"
#include "Resources/InputLayoutLibrary.h"
#include "Resources/ResourceManager.h"
#include "Resources/SamplerLibrary.h"

namespace Scene
{
    SceneSystem::SceneSystem(Resources::ResourceManager& resourceManager, Graphics::RenderSystem& renderSystem)
        : _resourceManager(resourceManager), _renderSystem(renderSystem)
    {}

    void SceneSystem::AddSceneObject(const std::string_view name, SceneObject sceneNode)
    {
        _sceneObjects.emplace(std::string(name), std::make_unique<SceneObject>(std::move(sceneNode)));
    }

    void SceneSystem::AddSceneNode(SceneNode sceneNode)
    {
        _sceneNodes.push_back(std::make_unique<SceneNode>(std::move(sceneNode)));
    }

    SceneObject* SceneSystem::GetSceneObject(const std::string_view name)
    {
        auto it = _sceneObjects.find(name);
        if (it == _sceneObjects.end())
        {
            LoadObject(name);
            it = _sceneObjects.find(name);
        }

        return it->second.get();
    }

    void SceneSystem::Build()
    {
        for (const auto& object : _sceneObjects | std::views::values)
        {
            object->ClearInstances();
        }
        for (const auto& node : _sceneNodes)
        {
            node->GetSceneObject()->AddInstance(node->GetWorldMatrix());
        }
    }

    void SceneSystem::LoadObject(const std::string_view name)
    {
        const auto& material = _resourceManager.GetMaterial("Default");
        const auto& cube = _resourceManager.GetMesh("Cube");

        auto object = Graphics::RenderObjectBuilder(_renderSystem.GetDevice())
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

        _sceneObjects.emplace(std::string(name), std::make_unique<SceneObject>(std::move(object)));
    }
}
