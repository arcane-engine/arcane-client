#pragma once

#include "BlendStateLibrary.h"
#include "Resources/DepthStencilStateLibrary.h"
#include "Resources/InputLayoutLibrary.h"
#include "Resources/MaterialLibrary.h"
#include "Resources/MeshLibrary.h"
#include "Resources/SamplerLibrary.h"
#include "Resources/ShaderLibrary.h"
#include "Resources/TextureLibrary.h"

namespace Resources
{
    class ResourceManager
    {
    public:
        explicit ResourceManager(Graphics::Device& device);

        [[nodiscard]] ShaderLibrary& GetShaderLibrary();
        [[nodiscard]] TextureLibrary& GetTextureLibrary();
        [[nodiscard]] MaterialLibrary& GetMaterialLibrary();
        [[nodiscard]] MeshLibrary& GetMeshLibrary();
        [[nodiscard]] SamplerLibrary& GetSamplerLibrary();
        [[nodiscard]] DepthStencilStateLibrary& GetDepthStencilStateLibrary();
        [[nodiscard]] InputLayoutLibrary& GetInputLayoutLibrary();

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetVertexShader(std::string_view name, bool instanced = false);
        [[nodiscard]] ID3DBlob* GetVertexShaderBlob(std::string_view name, bool instanced = false);
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetPixelShader(std::string_view name);
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetTexture(std::string_view name);
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetHeightmapTexture(std::string_view name);
        [[nodiscard]] const Material& GetMaterial(std::string_view name);
        [[nodiscard]] const Mesh& GetMesh(std::string_view name);
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11SamplerState>& GetSampler(SamplerType type) const;
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& GetDepthStencilState(DepthStencilStateType type) const;
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11BlendState>& GetBlendState(BlendStateType type) const;
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11InputLayout>& GetInputLayout(InputLayoutType type) const;

    private:
        ShaderLibrary _shaderLibrary;
        TextureLibrary _textureLibrary;
        MaterialLibrary _materialLibrary;
        MeshLibrary _meshLibrary;
        SamplerLibrary _samplerLibrary;
        DepthStencilStateLibrary _depthStencilStateLibrary;
        BlendStateLibrary _blendStateLibrary;
        InputLayoutLibrary _inputLayoutLibrary;
    };
}
