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
        explicit SamplerLibrary(Graphics::Device& device);

        Microsoft::WRL::ComPtr<ID3D11SamplerState> GetSampler(SamplerType type);

    private:
        void CreateSampler(SamplerType type, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address);

        Graphics::Device& _device;
        std::array<Microsoft::WRL::ComPtr<ID3D11SamplerState>, 2> _samplers;
    };
}
