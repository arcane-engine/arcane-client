#pragma once

#include <DirectXMath.h>

#include "Core/Context/CameraContext.h"
#include "Core/Context/MouseInputContext.h"
#include "Graphics/Camera/CameraRotation.h"
#include "Math/Ray.h"
#include "Math/Vector3.h"

namespace Graphics
{
    class Camera
    {
    public:
        Camera(int width, int height) noexcept;

        void SetTarget(const Math::Vector3& target) noexcept;
        void SetDistance(float distance) noexcept;
        void SetResolution(int width, int height) noexcept;

        [[nodiscard]] const Math::Vector3& GetPosition() const noexcept;
        [[nodiscard]] const Math::Vector3& GetDirection() const noexcept;
        [[nodiscard]] const Math::Vector3& GetTarget() const noexcept;
        [[nodiscard]] float GetDistance() const noexcept;
        [[nodiscard]] DirectX::XMMATRIX GetViewMatrix() const noexcept;
        [[nodiscard]] DirectX::XMMATRIX GetProjectionMatrix() const noexcept;
        [[nodiscard]] DirectX::XMMATRIX GetViewProjectionMatrix() const noexcept;
        [[nodiscard]] Math::Ray GetRay() const noexcept;

        void Rotate(float pitch, float yaw, float roll) noexcept;

        [[nodiscard]] Core::CameraContext Update(const Core::MouseInputContext& mouse) noexcept;

    private:
        float _width;
        float _height;
        Math::Vector3 _position = { 0.0f, 0.0f, 0.0f };
        Math::Vector3 _target = { 0.0f, 0.0f, 0.0f };
        Math::Vector3 _direction = { 0.0f, 0.0f, 0.0f };
        float _distance = 5.0f;
        CameraRotation _pitch;
        CameraRotation _yaw;
        CameraRotation _roll;
        Math::Vector3 _up = { 0.0f, 1.0f, 0.0f };
    };
}
