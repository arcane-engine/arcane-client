#include "Resources/MeshLibrary.h"

#include <format>

#include "TerrainManager.h"
#include "Core/IO/FileStream.h"

namespace Resources
{
    Mesh::Mesh(std::vector<std::byte> vertexBuffer, const int stride, std::vector<std::uint32_t> indexBuffer)
        : _vertexBuffer(std::move(vertexBuffer)), _stride(stride), _indexBuffer(std::move(indexBuffer))
    {}

    const std::vector<std::byte>& Mesh::GetVertexBuffer() const
    {
        return _vertexBuffer;
    }

    int Mesh::GetStride() const
    {
        return _stride;
    }

    const std::vector<std::uint32_t>& Mesh::GetIndexBuffer() const
    {
        return _indexBuffer;
    }

    MeshLibrary::MeshLibrary()
    {
        _meshes.emplace("terrain_mesh", TerrainManager::GenerateMesh(128, 512));
    }

    void MeshLibrary::AddMesh(std::string_view name, const Mesh& mesh)
    {
        _meshes.emplace(name, mesh);
    }

    const Mesh& MeshLibrary::GetMesh(const std::string_view name)
    {
        auto it = _meshes.find(name);
        if (it == _meshes.end())
        {
            LoadMesh(name);
            it = _meshes.find(name);
        }

        return it->second;
    }

    void MeshLibrary::LoadMesh(std::string_view name)
    {
        const auto path = std::format(R"(C:\arcane\arcane-data\meshes\{}.bin)", name);
        std::ifstream file(path, std::ios::binary);

        auto vertexCount = 0;
        auto vertexStride = 0;
        auto indexCount = 0;

        file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
        file.read(reinterpret_cast<char*>(&vertexStride), sizeof(vertexStride));
        file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));

        auto size = vertexCount * vertexStride;
        std::vector<std::byte> vertexData(static_cast<std::size_t>(vertexCount * vertexStride));
        file.read(reinterpret_cast<char*>(vertexData.data()), size);

        size = static_cast<int>(indexCount * sizeof(std::uint32_t));
        std::vector<std::uint32_t> indices(indexCount);
        file.read(reinterpret_cast<char*>(indices.data()), size);

        _meshes.emplace(name, Mesh(std::move(vertexData), vertexStride, std::move(indices)));
    }
}
