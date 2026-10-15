#include "Core/Input/InputSystem.h"

namespace Core::Input
{
    InputContext InputSystem::Update(Platform::Window& window)
    {
        const auto& keyboard = window.GetKeyboard();
        auto& mouse = window.GetMouse();

        auto deltaX = 0.0f;
        auto deltaY = 0.0f;
        auto wheelDelta = 0.0f;

        while (const auto event = mouse.ReadRawEvent())
        {
            deltaX = deltaX + mouse.GetSmoothDelta(static_cast<float>(event->X));
            deltaY = deltaY + mouse.GetSmoothDelta(static_cast<float>(event->Y));
        }

        while (const auto event = mouse.ReadEvent())
        {
            if (event->Type == MouseEventType::WheelUp)
            {
                wheelDelta = wheelDelta + 1.0f;
            }
            if (event->Type == MouseEventType::WheelDown)
            {
                wheelDelta = wheelDelta - 1.0f;
            }
        }

        auto input = InputContext
        {
            .Keyboard = {
                .Forward = keyboard.IsKeyDown('W'),
                .Backward = keyboard.IsKeyDown('S'),
                .Left = keyboard.IsKeyDown('A'),
                .Right = keyboard.IsKeyDown('D'),
            },
            .Mouse = {
                .LeftPressed = mouse.IsLeftPressed(),
                .RightPressed = mouse.IsRightPressed(),
                .DeltaX = deltaX,
                .DeltaY = deltaY,
                .WheelDelta = wheelDelta
            }
        };

        if (input.Keyboard != _input.Keyboard)
        {
            input.Keyboard.Changed = true;
        }

        _input = input;

        return _input;
    }
}