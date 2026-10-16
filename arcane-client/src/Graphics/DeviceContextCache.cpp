#include "Graphics/DeviceContextCache.h"

namespace Graphics
{
    DeviceContextCache::DeviceContextCache()
    {
        PixelShader = nullptr;
        VertexShader = nullptr;
        DepthStencilState = nullptr;
        InputLayout = nullptr;
        IndexBuffer = nullptr;
        VertexBuffer = nullptr;
        VertexShaderConstantBuffers.fill(nullptr);
        PixelShaderConstantBuffers.fill(nullptr);
        VertexShaderSamplers.fill(nullptr);
        PixelShaderSamplers.fill(nullptr);
        VertexShaderTextures.fill(nullptr);
        PixelShaderTextures.fill(nullptr);
        Topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    }

    void DeviceContextCache::ResetTextures() noexcept
    {
        VertexShaderTextures.fill(nullptr);
        PixelShaderTextures.fill(nullptr);
    }
}
