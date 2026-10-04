#pragma once

#include "Core/Platform/Window.h"
#include "Graphics/Device.h"
#include "Graphics/RenderObject.h"
#include "Graphics/RenderPipeline.h"
#include "Graphics/RenderQueue.h"
#include "Graphics/Camera/Camera.h"
#include "Resources/DepthStencilStateLibrary.h"
#include "Resources/MaterialLibrary.h"
#include "Resources/MeshLibrary.h"
#include "Resources/SamplerLibrary.h"
#include "Resources/ShaderLibrary.h"
#include "Resources/TextureLibrary.h"

namespace Core
{
    class Application
    {
    public:
        Application(int width, int height);

        int Run();

    private:
        void Update();

        void ToggleFullscreen();

        Platform::Window _window;
        Graphics::Device _device;
        Graphics::RenderPipeline _renderPipeline;
        Graphics::RenderQueue _renderQueue;
        Graphics::Camera _camera;
        Resources::ShaderLibrary _shaderLibrary;
        Resources::TextureLibrary _textureLibrary;
        Resources::MaterialLibrary _materialLibrary;
        Resources::MeshLibrary _meshLibrary;
        Resources::SamplerLibrary _samplerLibrary;
        Resources::DepthStencilStateLibrary _depthStencilStateLibrary;
        Graphics::RenderObject _cameraObject;
        Graphics::RenderObject _object;
    };
}
