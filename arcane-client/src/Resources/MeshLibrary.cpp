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

    Mesh* MeshLibrary::GetMesh(const std::string& name)
    {
        auto it = _meshes.find(name);
        if (it == _meshes.end())
        {
            LoadTexture(name);
            it = _meshes.find(name);
        }

        return it->second.get();
    }

    void MeshLibrary::LoadTexture(const std::string& name)
    {
        const auto reader = Core::IO::BinaryReader(std::make_unique<Core::IO::FileStream>(std::format(R"(C:\arcane\arcane-tools\data\{}.bin)", name)));

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

        _meshes[name] = std::make_unique<Mesh>(vertices, indices);
    }
}
