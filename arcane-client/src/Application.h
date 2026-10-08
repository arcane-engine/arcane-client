#pragma once

#include "Platform/Window.h"
#include "Graphics/Device.h"
#include "Graphics/RenderObject.h"
#include "Graphics/RenderPipeline.h"
#include "Graphics/RenderQueue.h"
#include "Graphics/Camera/Camera.h"
#include "Network/NetworkClient.h"
#include "Resources/DepthStencilStateLibrary.h"
#include "Resources/InputLayoutLibrary.h"
#include "Resources/MaterialLibrary.h"
#include "Resources/MeshLibrary.h"
#include "Resources/SamplerLibrary.h"
#include "Resources/ShaderLibrary.h"
#include "Resources/TextureLibrary.h"
#include "Core/Time/Timer.h"

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
    Core::Timer _timer;
    Network::NetworkClient _networkClient;
    Graphics::RenderPipeline _renderPipeline;
    Graphics::RenderQueue _renderQueue;
    Graphics::Camera _camera;
    Resources::ShaderLibrary _shaderLibrary;
    Resources::TextureLibrary _textureLibrary;
    Resources::MaterialLibrary _materialLibrary;
    Resources::MeshLibrary _meshLibrary;
    Resources::SamplerLibrary _samplerLibrary;
    Resources::DepthStencilStateLibrary _depthStencilStateLibrary;
    Resources::InputLayoutLibrary _inputLayoutLibrary;
    Graphics::RenderObject _cameraObject;
    Graphics::RenderObject _object1;
    Graphics::RenderObject _object2;
};
