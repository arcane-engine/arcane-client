#include "Resources/MeshLibrary.h"

#include <format>

#include "TerrainManager.h"
#include "Core/IO/BinaryReader.h"
#include "Core/IO/FileStream.h"

namespace Resources
{
    Mesh::Mesh(std::vector<std::byte> vertexBuffer, std::vector<std::uint32_t> indexBuffer, const int stride)
        : _vertexBuffer(std::move(vertexBuffer)), _indexBuffer(std::move(indexBuffer)), _stride(stride)
    {}

    const std::vector<std::byte>& Mesh::GetVertexBuffer() const
    {
        return _vertexBuffer;
    }

    const std::vector<std::uint32_t>& Mesh::GetIndexBuffer() const
    {
        return _indexBuffer;
    }

    int Mesh::GetStride() const
    {
        return _stride;
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
        auto reader = Core::IO::BinaryReader::FromFile(std::format(R"(C:\arcane\arcane-data\meshes\{}.bin)", name));

        const auto vertexCount = static_cast<std::size_t>(reader.Read<int>());
        const auto indexCount = static_cast<std::size_t>(reader.Read<int>());
        const auto stride = reader.Read<int>();

        const auto vertexBuffer = reader.Read<std::byte>(vertexCount * stride);
        const auto indexBuffer = reader.Read<std::uint32_t>(indexCount);

        _meshes.emplace(name, Mesh(vertexBuffer, indexBuffer, stride));
    }
}
