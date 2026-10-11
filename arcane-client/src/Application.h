#pragma once

#include "Platform/Window.h"
#include "Graphics/RenderObject.h"
#include "Graphics/Camera/Camera.h"
#include "Resources/ResourceManager.h"
#include "Core/Time/Timer.h"
#include "Graphics/RenderSystem.h"
#include "Network/NetworkWorker.h"

class Application
{
public:
    Application(int width, int height);

    int Run();
    void DrawCursor();

private:
    void Update();

    void ToggleFullscreen();

    Platform::Window _window;
    Core::Timer _timer;
    Network::NetworkWorker _networkWorker;
    Graphics::Camera _camera;
    Graphics::RenderSystem _renderSystem;
    Resources::ResourceManager _resourceManager;
    Graphics::RenderObject _cameraObject;
    Graphics::RenderObject _object1;
    Graphics::RenderObject _object2;
    Graphics::RenderObject _object3;
};
