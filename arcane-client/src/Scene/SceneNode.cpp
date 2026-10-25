#include "SceneNode.h"

#include <optional>

namespace Scene
{
    SceneNode::SceneNode(SceneObject* sceneObject, const Math::Vector3& position, const Math::Quaternion& rotation, const Math::Vector3& scale) :
        _sceneObject(sceneObject), _position(position), _rotation(rotation), _scale(scale)
    {}

    void SceneNode::SetSceneObject(SceneObject* sceneObject)
    {
        _sceneObject = sceneObject;
    }

    void SceneNode::SetPosition(const Math::Vector3& position)
    {
        _position = position;
        _worldMatrix = std::nullopt;
    }

    void SceneNode::SetRotation(const Math::Quaternion& rotation)
    {
        _rotation = rotation;
        _worldMatrix = std::nullopt;
    }

    void SceneNode::SetScale(const Math::Vector3& scale)
    {
        _scale = scale;
        _worldMatrix = std::nullopt;
    }

    SceneObject* SceneNode::GetSceneObject() const
    {
        return _sceneObject;
    }

    DirectX::XMMATRIX& SceneNode::GetWorldMatrix()
    {
        if (_worldMatrix == std::nullopt)
        {
            _worldMatrix = _scale.GetScalingMatrix() * _rotation.GetRotationMatrix() * _position.GetTranslationMatrix();
        }
        return _worldMatrix.value();
    }
}
