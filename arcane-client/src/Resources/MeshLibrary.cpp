#include "Resources/MeshLibrary.h"

#include <format>

#include "Core/IO/BinaryReader.h"
#include "Core/IO/FileStream.h"

namespace Resources
{
    Mesh::Mesh(std::vector<Graphics::Vertex> vertices, std::vector<unsigned int> indices)
        : _vertices(std::move(vertices)), _indices(std::move(indices))
    {}

    const std::vector<Graphics::Vertex>& Mesh::GetVertices() const
    {
        return _vertices;
    }

    const std::vector<unsigned int>& Mesh::GetIndices() const
    {
        return _indices;
    }

    const Mesh& MeshLibrary::GetMesh(const std::string_view name)
    {
        auto it = _meshes.find(name);
        if (it == _meshes.end())
        {
            LoadTexture(name);
            it = _meshes.find(name);
        }

        return it->second;
    }

    void MeshLibrary::LoadTexture(std::string_view name)
    {
        auto path = std::format(R"(C:\arcane\arcane-data\meshes\{}.bin)", name);
        const auto reader = Core::IO::BinaryReader(std::make_unique<Core::IO::FileStream>(path));

        auto vertices = std::vector<Graphics::Vertex>{};
        auto indices = std::vector<unsigned int>{};

        auto count = reader.ReadInt();
        for (auto i = 0; i < count; i++)
        {
            const auto x = reader.ReadFloat();
            const auto y = reader.ReadFloat();
            const auto z = reader.ReadFloat();
            const auto u = reader.ReadFloat();
            const auto v = reader.ReadFloat();
            
            vertices.push_back(Graphics::Vertex{ x, y, z, u, v });
        }

        count = reader.ReadInt();
        for (auto i = 0; i < count; i++)
        {
            const auto index = reader.ReadUInt();

            indices.push_back(index);
        }

        _meshes.emplace(name, Mesh(vertices, indices));
    }
}
