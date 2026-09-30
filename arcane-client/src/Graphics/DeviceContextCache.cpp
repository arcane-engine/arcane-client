#include "DeviceContextCache.h"

namespace Graphics
{
    DeviceContextCache::DeviceContextCache()
    {
        PixelShader = nullptr;
        VertexShader = nullptr;
        InputLayout = nullptr;
        IndexBuffer = nullptr;
        VertexBuffer = nullptr;
        VertexShaderConstantBuffers.fill(nullptr);
        PixelShaderConstantBuffers.fill(nullptr);
        Samplers.fill(nullptr);
        Textures.fill(nullptr);
        Topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    }
}
