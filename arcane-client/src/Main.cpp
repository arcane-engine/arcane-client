#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "Application.h"
#include "Core/Common/Exception.h"

int CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    try
    {

        auto application = Application(640, 480);

        application.Run();

        return 0;
    }
    catch (const Core::Exception& e)
    {
        MessageBoxA(nullptr, e.GetDescription().c_str(), e.GetType(), MB_OK | MB_ICONERROR);
    }
    catch (const std::exception& e)
    {
        MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONERROR);
    }
    catch (...)
    {
        MessageBoxA(nullptr, "An unknown error occurred.", "Unknown Exception", MB_OK | MB_ICONERROR);
    }

    return -1;
}
