#include "Resources/MaterialLibrary.h"

#include <format>

#include "Core/IO/BinaryReader.h"
#include "Core/IO/FileStream.h"

namespace Resources
{
    const Material& MaterialLibrary::GetMaterial(const std::string_view name)
    {
        auto it = _materials.find(name);
        if (it == _materials.end())
        {
            LoadMaterial(name);
            it = _materials.find(name);
        }

        return it->second;
    }

    void MaterialLibrary::LoadMaterial(std::string_view name)
    {
        auto reader = Core::IO::BinaryReader::FromFile(std::format(R"(C:\arcane\arcane-data\materials\{}.bin)", name));

        auto material = Material{};
        material.Shaders.VertexShader = reader.Read<std::string>();
        material.Shaders.PixelShader = reader.Read<std::string>();
        material.Textures.Albedo = reader.Read<std::string>();

        _materials.emplace(name, std::move(material));
    }
}
