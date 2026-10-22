#pragma once

namespace Scene
{
    inline auto SceneSystem::GetSceneObjectsView()
    {
        return _sceneObjects | std::views::values;
    }
}
