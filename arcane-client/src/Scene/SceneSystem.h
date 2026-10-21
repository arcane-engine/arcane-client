#pragma once

#include <memory>
#include <ranges>
#include <string>
#include <unordered_map>

#include "Core/Common/StringHash.h"
#include "Scene/SceneNode.h"
#include "Scene/SceneObject.h"

namespace Graphics
{
    class RenderSystem;
}

namespace Resources
{
    class ResourceManager;
}

namespace Scene
{
    class SceneSystem
    {
    public:
        SceneSystem(Resources::ResourceManager& resourceManager, Graphics::RenderSystem& renderSystem);

        void AddObject(std::string_view key, SceneObject object);
        void AddNode(SceneNode node);

        [[nodiscard]] auto GetObjectsView() { return _objects | std::views::values; }
        [[nodiscard]] SceneObject* GetObject(std::string_view key);

        void Build();

    private:
        void LoadObject(std::string_view key);

        Resources::ResourceManager& _resourceManager;
        Graphics::RenderSystem& _renderSystem;

        std::unordered_map<std::string, std::unique_ptr<SceneObject>, Core::StringHash, std::equal_to<>> _objects;
        std::vector<std::unique_ptr<SceneNode>> _nodes;
    };
}
