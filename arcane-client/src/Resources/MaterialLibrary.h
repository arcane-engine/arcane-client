#pragma once

#include <string>
#include <unordered_map>

#include "Core/Common/StringHash.h"

namespace Resources
{
    struct Shaders
    {
        std::string VertexShader;
        std::string PixelShader;
    };

    struct Textures
    {
        std::string Albedo;
    };

    struct Material
    {
        Shaders Shaders;
        Textures Textures;
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
