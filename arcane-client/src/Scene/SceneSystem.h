#pragma once

#include <memory>
#include <ranges>
#include <string>
#include <unordered_map>

#include "Core/Common/StringHash.h"
#include "Scene/SceneNode.h"
#include "Scene/SceneObject.h"

namespace Graphics { class RenderSystem; }
namespace Resources { class ResourceManager; }

namespace Scene
{
    class SceneSystem
    {
    public:
        SceneSystem(Resources::ResourceManager& resourceManager, Graphics::RenderSystem& renderSystem);

        void AddSceneObject(std::string_view name, SceneObject sceneNode);
        void AddSceneNode(SceneNode sceneNode);

        [[nodiscard]] auto GetSceneObjectsView();
        [[nodiscard]] SceneObject* GetSceneObject(std::string_view mesh, std::string_view material);

        void Build();

    private:
        void LoadObject(std::string_view mesh, std::string_view material);

        Resources::ResourceManager& _resourceManager;
        Graphics::RenderSystem& _renderSystem;

        std::unordered_map<std::string, std::unique_ptr<SceneObject>, Core::StringHash, std::equal_to<>> _sceneObjects;
        std::vector<std::unique_ptr<SceneNode>> _sceneNodes;
    };
}

#include "Scene/SceneSystem.inl"
