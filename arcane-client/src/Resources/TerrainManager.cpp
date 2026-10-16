#include "TerrainManager.h"

#include "Math/Vector3.h"

namespace Resources
{
    Mesh TerrainManager::GenerateMesh(const int gridSize, const int terrainSize, const int stride)
    {
        std::vector<std::byte> vertexBuffer(gridSize * gridSize * stride);

        auto* vertices = reinterpret_cast<Math::Vector3*>(vertexBuffer.data());
        int vertexIndex = 0;
        for (int z = 0; z < gridSize; z++)
        {
            for (int x = 0; x < gridSize; x++)
            {
                const float u = static_cast<float>(x) / static_cast<float>(gridSize - 1);
                const float v = static_cast<float>(z) / static_cast<float>(gridSize - 1);

                vertices[vertexIndex++] = { (u - 0.5f) * static_cast<float>(terrainSize), 0.0f, (v - 0.5f) * static_cast<float>(terrainSize) };
            }
        }

        const auto quads = gridSize - 1;
        std::vector<uint32_t> indexBuffer;
        indexBuffer.reserve(quads * quads * 6);

        for (int z = 0; z < quads; z++)
        {
            for (int x = 0; x < quads; x++)
            {
                uint32_t v1 = z * gridSize + x;
                uint32_t v2 = v1 + 1;
                uint32_t v3 = (z + 1) * gridSize + x;
                uint32_t v4 = v3 + 1;

                indexBuffer.push_back(v1);
                indexBuffer.push_back(v3);
                indexBuffer.push_back(v2);

                indexBuffer.push_back(v2);
                indexBuffer.push_back(v3);
                indexBuffer.push_back(v4);
            }
        }

        return Mesh(vertexBuffer, stride, indexBuffer);
    }
}
