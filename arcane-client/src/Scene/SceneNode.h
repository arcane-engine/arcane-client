#pragma once

#include <vector>

#include "Math/Quaternion.h"
#include "Math/Vector3.h"

namespace Scene
{
    class SceneObject;

    class SceneNode
    {
    public:
        void SetSceneObject(SceneObject* sceneObject);

        SceneObject* GetSceneObject();
        DirectX::XMMATRIX GetWorldMatrix();

    private:
        Math::Vector3 _position;
        Math::Quaternion _rotation;
        Math::Vector3 _scale;
        DirectX::XMMATRIX _worldTransform;
        std::vector<SceneNode> _sceneNodes;
        SceneObject* _sceneObject;
    };
}
