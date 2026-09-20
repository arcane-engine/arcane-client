#pragma once


namespace Core::Input
{
    class MouseRawEvent
    {
    public:
        MouseRawEvent(int x, int y) noexcept;

        [[nodiscard]] int GetX() const noexcept;
        [[nodiscard]] int GetY() const noexcept;

    private:
        int _x;
        int _y;
    };
}
