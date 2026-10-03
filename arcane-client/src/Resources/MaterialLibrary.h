#pragma once

#include <string>
#include <unordered_map>

#include "Core/StringHash.h"

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
        [[nodiscard]] const Material& GetMaterial(std::string_view name);

    private:
        void LoadMaterial(std::string_view name);

        std::unordered_map<std::string, Material, Core::StringHash, std::equal_to<>> _materials;
    };
}
