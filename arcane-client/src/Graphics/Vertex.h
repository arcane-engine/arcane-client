#pragma once

namespace Graphics
{
    struct Vertex
    {
        float X;
        float Y;
        float Z;
        float NormalX;
        float NormalY;
        float NormalZ;
        float U;
        float V;
    };

    struct CompositionVertex
    {
        float X;
        float Y;
        float Z;
        float U;
        float V;
    };

    struct UserInterfaceVertex
    {
        float X;
        float Y;
        float Z;
        float U;
        float V;
    };
}