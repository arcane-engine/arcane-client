#pragma once

#include <string>
#include <unordered_map>

#include "Core/Common/StringHash.h"
#include "Graphics/Vertex.h"

namespace Resources
{
    class Mesh
    {
    public:
        Mesh(std::vector<std::byte> vertexBuffer, int stride, std::vector<unsigned int> indexBuffer);

        [[nodiscard]] const std::vector<std::byte>& GetVertexBuffer() const;
        [[nodiscard]] int GetStride() const;
        [[nodiscard]] const std::vector<unsigned int>& GetIndexBuffer() const;

    private:
        std::vector<std::byte> _vertexBuffer;
        int _stride;
        std::vector<unsigned int> _indexBuffer;
    };

    class MeshLibrary
    {
    public:
        [[nodiscard]] const Mesh& GetMesh(std::string_view name);

    private:
        void LoadMesh(std::string_view name);

        std::unordered_map<std::string, Mesh, Core::StringHash, std::equal_to<>> _meshes;
    };
}
