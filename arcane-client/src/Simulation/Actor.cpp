#include "Actor.h"

namespace Simulation
{
    Actor::Actor(const std::uint32_t id, const Math::Vector3& position, const Math::Quaternion& rotation, const Math::Vector3& scale, const Math::Vector3& velocity)
        : _id(id), _position(position), _rotation(rotation), _scale(scale), _velocity(velocity)
    {}

    std::uint32_t Actor::GetId() const
    {
        return _id;
    }

    const Math::Vector3& Actor::GetPosition() const
    {
        return _position;
    }

    const Math::Vector3& Actor::GetVelocity() const
    {
        return _velocity;
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

    void Actor::SetVelocity(const Math::Vector3& velocity)
    {
        _velocity = velocity;
    }

    void Actor::SetRotation(const Math::Quaternion& rotation)
    {
        _rotation = rotation;
    }

    void Actor::SetScale(const Math::Vector3& scale)
    {
        _scale = scale;
    }

    void Actor::Update(const Core::TimeContext& time)
    {
        _position = _position + _velocity * time.Delta;
    }
}
