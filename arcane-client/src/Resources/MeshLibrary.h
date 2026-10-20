#pragma once

#include <string>
#include <unordered_map>

#include "Core/Common/StringHash.h"

namespace Resources
{
    class Mesh
    {
    public:
        Mesh(std::vector<std::byte> vertexBuffer, std::vector<std::uint32_t> indexBuffer, int stride);

        [[nodiscard]] const std::vector<std::byte>& GetVertexBuffer() const;
        [[nodiscard]] const std::vector<std::uint32_t>& GetIndexBuffer() const;
        [[nodiscard]] int GetStride() const;

    private:
        std::vector<std::byte> _vertexBuffer;
        std::vector<std::uint32_t> _indexBuffer;
        int _stride;
    };

    class MeshLibrary
    {
    public:
        MeshLibrary();

        void AddMesh(std::string_view name, const Mesh& mesh);

        [[nodiscard]] const Mesh& GetMesh(std::string_view name);

    private:
        void LoadMesh(std::string_view name);

        std::unordered_map<std::string, Mesh, Core::StringHash, std::equal_to<>> _meshes;
    };
}
