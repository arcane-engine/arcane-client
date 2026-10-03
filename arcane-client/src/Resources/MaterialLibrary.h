#pragma once

#include <string>
#include <unordered_map>

namespace Resources
{
    struct Material
    {
        std::string VertexShader;
        std::string PixelShader;
        std::string AlbedoTexture;
    };

    class MaterialLibrary
    {
    public:
        [[nodiscard]] const Material& GetMaterial(const std::string& name);

    private:
        void LoadMaterial(const std::string& name);

        std::unordered_map<std::string, Material> _materials;
    };
}
