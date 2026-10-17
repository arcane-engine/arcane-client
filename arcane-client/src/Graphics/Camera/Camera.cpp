#include "Graphics/Camera/Camera.h"

#include "Core/Context/InputContext.h"

namespace Graphics
{
    Camera::Camera(const int width, const int height) noexcept
        : _width(static_cast<float>(width)), _height(static_cast<float>(height)), _pitch(-PI / 2 + EPSILON, PI / 2 - EPSILON)
    {
    }

    void Camera::SetTarget(const Math::Vector3& target) noexcept
    {
        _target = target;
    }

    void Camera::SetDistance(const float distance) noexcept
    {
        _distance = distance;
    }

    void Camera::SetResolution(const int width, const int height) noexcept
    {
        _width = static_cast<float>(width);
        _height = static_cast<float>(height);
    }

    const Math::Vector3& Camera::GetPosition() const noexcept
    {
        return _position;
    }

    const Math::Vector3& Camera::GetDirection() const noexcept
    {
        return _direction;
    }

    const Math::Vector3& Camera::GetTarget() const noexcept
    {
        return _target;
    }

    float Camera::GetDistance() const noexcept
    {
        return _distance;
    }

    DirectX::XMMATRIX Camera::GetViewMatrix() const noexcept
    {
        return DirectX::XMMatrixLookAtLH(static_cast<DirectX::XMVECTOR>(_position), static_cast<DirectX::XMVECTOR>(_target), static_cast<DirectX::XMVECTOR>(_up));
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

    Core::CameraContext Camera::Update(const Core::InputContext& input) noexcept
    {
        if (input.Mouse.RightPressed)
        {
            Rotate(-input.Mouse.DeltaY, input.Mouse.DeltaX, 0.0f);
        }

        _distance = _distance - input.Mouse.WheelDelta;

        _direction.X = Math::Cos(_pitch.GetValue()) * Math::Sin(_yaw.GetValue());
        _direction.Y = Math::Sin(_pitch.GetValue());
        _direction.Z = Math::Cos(_pitch.GetValue()) * Math::Cos(_yaw.GetValue());
        _direction.Normalize();

        if (input.Keyboard.Forward)
        {
            _target.X += 0.05f;
        }

        _position = _target - _direction * _distance;

        return {
            .Target = _target,
            .ViewMatrix = GetViewMatrix(),
            .ProjectionMatrix = GetProjectionMatrix(),
            .ViewProjectionMatrix = GetViewProjectionMatrix()
        };
    }
}
