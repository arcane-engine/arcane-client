#pragma once

#include <DirectXMath.h>

#include "Graphics/Camera/CameraRotation.h"
#include "Math/Vector3.h"

namespace Graphics
{
    class Camera
    {
    public:
        Camera(int width, int height) noexcept;

        void SetPosition(const Math::Vector3& position) noexcept;

        [[nodiscard]] Math::Vector3 GetPosition() const noexcept;
        [[nodiscard]] Math::Vector3 GetDirection() const noexcept;
        [[nodiscard]] DirectX::XMMATRIX GetViewMatrix() const noexcept;
        [[nodiscard]] DirectX::XMMATRIX GetProjectionMatrix() const noexcept;

        void Rotate(float pitch, float yaw, float roll) noexcept;
        void Update() noexcept;

    private:

        float _width;
        float _height;
        Math::Vector3 _position = { 0.0f, 0.0f, 0.0f };
        Math::Vector3 _direction = { 0.0f, 0.0f, 1.0f };
        CameraRotation _pitch;
        CameraRotation _yaw;
        CameraRotation _roll;
        Math::Vector3 _up = { 0.0f, 1.0f, 0.0f };
    };
}
