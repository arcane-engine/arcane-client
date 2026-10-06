#pragma once

#include <array>
#include <d3d11.h>
#include <unordered_map>
#include <wrl/client.h>

namespace Graphics
{
    class Device;
}

namespace Resources
{
    enum class SamplerType : std::uint8_t
    {
        LinearWrap,
        LinearClamp
    };

    class SamplerLibrary
    {
    public:
        explicit SamplerLibrary(const Graphics::Device& device);

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11SamplerState>& GetSampler(SamplerType type);

    private:
        void CreateSampler(const Graphics::Device& device, SamplerType type, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address);

        std::array<Microsoft::WRL::ComPtr<ID3D11SamplerState>, 2> _samplers;
    };
}
