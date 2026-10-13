#include "Graphics/Camera/Camera.h"

namespace Graphics
{
    Camera::Camera(const int width, const int height) noexcept
        : _width(static_cast<float>(width)), _height(static_cast<float>(height)), _pitch(-PI / 2 + EPSILON, PI / 2 - EPSILON)
    {
    }

    void Camera::SetPosition(const Math::Vector3& position) noexcept
    {
        _position = position;
    }

    void Camera::SetResolution(const int width, const int height) noexcept
    {
        _width = static_cast<float>(width);
        _height = static_cast<float>(height);
    }

    Math::Vector3 Camera::GetPosition() const noexcept
    {
        return _position;
    }

    Math::Vector3 Camera::GetDirection() const noexcept
    {
        return _direction;
    }

    DirectX::XMMATRIX Camera::GetViewMatrix() const noexcept
    {
        return DirectX::XMMatrixLookToLH(static_cast<DirectX::XMVECTOR>(_position), static_cast<DirectX::XMVECTOR>(_direction), static_cast<DirectX::XMVECTOR>(_up));
    }

    DirectX::XMMATRIX Camera::GetProjectionMatrix() const noexcept
    {
        return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), _width / _height, 0.5f, 500.0f);
    }

    DirectX::XMMATRIX Camera::GetViewProjectionMatrix() const noexcept
    {
        return GetViewMatrix() * GetProjectionMatrix();
    }

    Math::Ray Camera::GetRay() const noexcept
    {
        return { _position, _direction };
    }

    void Camera::Rotate(const float pitch, const float yaw, const float roll) noexcept
    {
        _pitch.Rotate(pitch);
        _yaw.Rotate(yaw);
        _roll.Rotate(roll);
    }

    Core::CameraContext Camera::Update(const Core::MouseInputContext& mouse) noexcept
    {
        if (mouse.RightPressed)
        {
            Rotate(-mouse.DeltaY, mouse.DeltaX, 0.0f);

            _direction = DirectX::XMVector3Normalize(
                DirectX::XMVectorSet(
                    Math::Cos(_pitch.GetValue()) * Math::Sin(_yaw.GetValue()),
                    Math::Sin(_pitch.GetValue()),
                    Math::Cos(_pitch.GetValue()) * Math::Cos(_yaw.GetValue()),
                    0.0f
                )
            );
        }

        return {
            .ViewMatrix = GetViewMatrix(),
            .ProjectionMatrix = GetProjectionMatrix(),
            .ViewProjectionMatrix = GetViewProjectionMatrix()
        };
    }
}
