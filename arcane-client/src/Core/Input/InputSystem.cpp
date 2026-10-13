#include "Core/Input/InputSystem.h"

namespace Core::Input
{
    std::optional<Network::ClientInputPacket> InputSystem::PollInput(Platform::Window& window)
    {
        const auto& keyboard = window.GetKeyboard();

        const auto input = Network::ClientInputPacket
        {
            .Forward = keyboard.IsKeyDown('W'),
            .Backward = keyboard.IsKeyDown('S'),
            .Left = keyboard.IsKeyDown('A'),
            .Right = keyboard.IsKeyDown('D'),
        };

        if (input == _input)
        {
            return std::nullopt;
        }
        _input = input;

        return _input;
    }
}