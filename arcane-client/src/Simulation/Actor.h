#pragma once

#include <cstdint>

#include "Core/Context/Context.h"
#include "Math/Quaternion.h"
#include "Math/Vector3.h"

namespace Simulation
{
    class Actor
    {
    public:
        Actor(std::uint32_t id, const Math::Vector3& position, const Math::Quaternion& rotation, const Math::Vector3& scale);

        [[nodiscard]] std::uint32_t GetId() const;
        [[nodiscard]] const Math::Vector3& GetPosition() const;
        [[nodiscard]] const Math::Vector3& GetVelocity() const;
        [[nodiscard]] const Math::Quaternion& GetRotation() const;
        [[nodiscard]] const Math::Vector3& GetScale() const;
        [[nodiscard]] DirectX::XMMATRIX GetWorldMatrix() const;

        void SetPosition(const Math::Vector3& position);
        void SetVelocity(const Math::Vector3& velocity);
        void SetRotation(const Math::Quaternion& rotation);
        void SetScale(const Math::Vector3& scale);

        void Update(const Core::TimeContext& time);

    private:
        std::uint32_t _id;
        Math::Vector3 _position;
        Math::Vector3 _velocity;
        Math::Quaternion _rotation;
        Math::Vector3 _scale;
    };
}
