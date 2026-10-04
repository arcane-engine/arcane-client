#pragma once

namespace Graphics
{
    class Vertex
    {
    public:
        float X;
        float Y;
        float Z;
        float NormalX;
        float NormalY;
        float NormalZ;
        float U;
        float V;
    };

    class CompositionVertex
    {
    public:
        float X;
        float Y;
        float Z;
        float U;
        float V;
    };
}