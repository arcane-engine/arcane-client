#pragma once

#include "Core/Input/InputSystem.h"
#include "Core/Time/Timer.h"
#include "Graphics/RenderObject.h"
#include "Graphics/RenderSystem.h"
#include "Graphics/Camera/Camera.h"
#include "Network/NetworkSystem.h"
#include "Network/NetworkWorker.h"
#include "Platform/Window.h"
#include "Resources/ResourceManager.h"

class Application
{
public:
    Application(int width, int height);

    int Run();

private:
    void Update();

    void ToggleFullscreen();

    Platform::Window _window;
    Core::Timer _timer;
    Network::NetworkSystem _networkSystem;
    Graphics::Camera _camera;
    Graphics::RenderSystem _renderSystem;
    Core::Input::InputSystem _inputSystem;
    Resources::ResourceManager _resourceManager;
    Graphics::RenderObject _cameraObject;
    Graphics::RenderObject _object1;
    Graphics::RenderObject _object2;
};
