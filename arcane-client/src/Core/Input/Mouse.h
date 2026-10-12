#pragma once

#include <optional>
#include <queue>

#include "Core/Input/MouseEvent.h"
#include "Core/Input/MouseRawEvent.h"
#include "Math/Ray.h"

namespace Graphics
{
    class Camera;
}

namespace Platform
{
    class Window;
}

namespace Core::Input
{
    class Mouse
    {
        friend class Platform::Window;

    public:
        Mouse(int width, int height);

        [[nodiscard]] int GetX() const noexcept;
        [[nodiscard]] int GetY() const noexcept;
        [[nodiscard]] float GetNormalizedX() const noexcept;
        [[nodiscard]] float GetNormalizedY() const noexcept;
        [[nodiscard]] const Math::Ray& GetRay() const noexcept;
        [[nodiscard]] float GetSmoothDelta(float value) noexcept;
        [[nodiscard]] bool IsInWindow() const noexcept;
        [[nodiscard]] bool IsLeftPressed() const noexcept;
        [[nodiscard]] bool IsRightPressed() const noexcept;
        [[nodiscard]] bool IsCaptured() const noexcept;
        [[nodiscard]] std::optional<MouseEvent> ReadEvent() noexcept;
        [[nodiscard]] std::optional<MouseRawEvent> ReadRawEvent() noexcept;
        [[nodiscard]] bool IsEmpty() const noexcept;

        void Flush() noexcept;
        void Update(const Graphics::Camera& camera) noexcept;

        void SetResolution(int width, int height) noexcept;
        void Capture() noexcept;
        void Release() noexcept;

    private:
        void OnMove(int x, int y);
        void OnMoveRaw(int x, int y);
        void OnEnter();
        void OnLeave();
        void OnLeftPressed(int x, int y);
        void OnLeftReleased(int x, int y);
        void OnRightPressed(int x, int y);
        void OnRightReleased(int x, int y);
        void OnWheelUp(int x, int y);
        void OnWheelDown(int x, int y);
        void OnWheelDelta(int x, int y, int delta);

        void TrimEventBuffer();
        void TrimRawEventBuffer();

        std::queue<MouseEvent> _eventBuffer;
        std::queue<MouseRawEvent> _rawEventBuffer;

        int _x = 0;
        int _y = 0;
        int _width;
        int _height;
        bool _captured = false;
        Math::Ray _ray = {};
        int _wheelDelta = 0;
        float _smoothAlpha = 0.8f;
        float _smoothDeltaX = 0.0f;
        float _smoothDeltaY = 0.0f;
        bool _leftPressed = false;
        bool _rightPressed = false;
        bool _inWindow = false;
    };
}