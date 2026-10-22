#pragma once

#include <optional>
#include <vector>

#include "Math/Quaternion.h"
#include "Math/Vector3.h"

namespace Scene
{
    class SceneObject;

    class SceneNode
    {
    public:
        SceneNode() = default;
        SceneNode(SceneObject* sceneObject, const Math::Vector3& position, const Math::Quaternion& rotation, const Math::Vector3& scale);

        void SetSceneObject(SceneObject* sceneObject);
        void SetPosition(const Math::Vector3& position);
        void SetRotation(const Math::Quaternion& rotation);
        void SetScale(const Math::Vector3& scale);

        [[nodiscard]] SceneObject* GetSceneObject() const;
        [[nodiscard]] DirectX::XMMATRIX& GetWorldMatrix();

    private:
        SceneObject* _sceneObject;
        Math::Vector3 _position;
        Math::Quaternion _rotation;
        Math::Vector3 _scale;
        std::optional<DirectX::XMMATRIX> _worldMatrix;
        std::vector<SceneNode> _sceneNodes;
    };
}
