#include "Actor.h"

namespace Simulation
{
    Actor::Actor(const std::uint32_t id, const Math::Vector3& position, const Math::Quaternion& rotation, const Math::Vector3& scale)
        : _id(id), _position(position), _rotation(rotation), _scale(scale)
    {}

    std::uint32_t Actor::GetId() const
    {
        return _id;
    }

    const Math::Vector3& Actor::GetPosition() const
    {
        return _position;
    }

    const Math::Quaternion& Actor::GetRotation() const
    {
        return _rotation;
    }

    const Math::Vector3& Actor::GetScale() const
    {
        return _scale;
    }

    DirectX::XMMATRIX Actor::GetWorldMatrix() const
    {
        return DirectX::XMMatrixAffineTransformation(static_cast<DirectX::XMVECTOR>(_scale), DirectX::XMVectorZero(), static_cast<DirectX::XMVECTOR>(_rotation), static_cast<DirectX::XMVECTOR>(_position));
    }

    void Actor::SetPosition(const Math::Vector3& position)
    {
        _position = position;
    }

    void Actor::SetRotation(const Math::Quaternion& rotation)
    {
        _rotation = rotation;
    }

    void Actor::SetScale(const Math::Vector3& scale)
    {
        _scale = scale;
    }
}
