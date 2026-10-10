#include "Resources/MeshLibrary.h"

#include <format>

#include "Core/IO/FileStream.h"

namespace Resources
{
    Mesh::Mesh(std::vector<std::byte> vertexBuffer, const int stride, std::vector<unsigned int> indexBuffer)
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

    const std::vector<unsigned int>& Mesh::GetIndexBuffer() const
    {
        return _indexBuffer;
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

        int vertexCount = 0;
        int vertexStride = 0;
        int indexCount = 0;

        file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
        file.read(reinterpret_cast<char*>(&vertexStride), sizeof(vertexStride));
        file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));

        std::vector<std::byte> vertexData(vertexCount * vertexStride);
        file.read(reinterpret_cast<char*>(vertexData.data()), static_cast<std::streamsize>(vertexCount * vertexStride));

        std::vector<unsigned int> indices(indexCount);
        file.read(reinterpret_cast<char*>(indices.data()), static_cast<std::streamsize>(indexCount * sizeof(unsigned int)));

        _meshes.emplace(name, Mesh(std::move(vertexData), vertexStride, std::move(indices)));
    }
}
