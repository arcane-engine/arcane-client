#include "Resources/MaterialLibrary.h"

#include <format>
#include <memory>

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
        auto path = std::format(R"(C:\arcane\arcane-data\materials\{}.bin)", name);
        const auto reader = Core::IO::BinaryReader(std::make_unique<Core::IO::FileStream>(path));

        auto material = Material{};
        material.VertexShader = reader.ReadString();
        material.PixelShader = reader.ReadString();
        material.AlbedoTexture = reader.ReadString();

        _materials.emplace(name, std::move(material));
    }
}
