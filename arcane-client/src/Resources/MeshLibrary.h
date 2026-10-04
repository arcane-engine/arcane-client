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
        Mesh(std::vector<Graphics::Vertex> vertices, std::vector<unsigned int> indices);

        [[nodiscard]] const std::vector<Graphics::Vertex>& GetVertices() const;
        [[nodiscard]] const std::vector<unsigned int>& GetIndices() const;

    private:
        std::vector<Graphics::Vertex> _vertices;
        std::vector<unsigned int> _indices;
    };

    class MeshLibrary
    {
    public:
        [[nodiscard]] const Mesh& GetMesh(std::string_view name);

    private:
        void LoadTexture(std::string_view name);

        std::unordered_map<std::string, Mesh, Core::StringHash, std::equal_to<>> _meshes;
    };
}
