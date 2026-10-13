#pragma once

namespace Core
{
    struct KeybordInputContext
    {
        bool Changed = false;
        bool Forward = false;
        bool Backward = false;
        bool Left = false;
        bool Right = false;

        auto operator==(const KeybordInputContext& input) const
        {
            return input.Forward == Forward && input.Backward == Backward && input.Left == Left && input.Right == Right;
        }
    };
}
