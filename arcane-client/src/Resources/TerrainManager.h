#pragma once

#include "Resources/MeshLibrary.h"

namespace Resources
{
    class TerrainManager
    {
    public:
        static Mesh GenerateMesh(int gridSize, int terrainSize, int stride = 12);
    };
}
