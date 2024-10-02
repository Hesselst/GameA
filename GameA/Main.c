#include <stdio.h>

#pragma warning(push, 3)
#pragma warning(disable:4668)
#pragma warning(disable:5105)
#include <windows.h>
#pragma warning(pop)

#include "Main.h"

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previousInstance, _In_ LPSTR cmdLine, _In_ int showCmd)
{
    UNREFERENCED_PARAMETER(instance);

    UNREFERENCED_PARAMETER(previousInstance);

    UNREFERENCED_PARAMETER(cmdLine);

    UNREFERENCED_PARAMETER(showCmd);

    if (GameIsAlreadyRunning() == TRUE)
    {
        MessageBoxA(NULL, "Another instance of this program is already running!", "Error!", MB_ICONEXCLAMATION | MB_OK);

        goto Exit;
    }

    if (CreateMainGameWindow() != ERROR_SUCCESS)
    {
        goto Exit;
    }


    MSG message = { 0 };

    while (GetMessageA(&message, NULL, 0, 0) > 0)
    {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }

Exit:

    return 0;
}

LRESULT CALLBACK MainWindowProc(_In_ HWND windowHandle, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    LRESULT result = 0;
    /*
    char buf[12] = { 0 };

    _itoa(message, buf, _countof(buf), 10);

    OutputDebugStringA(buf);
    OutputDebugStringA("\n");
    */

    switch (message)
    {
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            break;
        }
        default:
            result = DefWindowProcA(windowHandle, message, wParam, lParam);
    }
    return result;
}

DWORD CreateMainGameWindow(void)
{
    DWORD result = ERROR_SUCCESS;


    WNDCLASSEXA windowClass = { 0 };

    HWND windowHandle = { 0 };



    windowClass.cbSize = sizeof(WNDCLASSEXA);

    windowClass.style = 0;

    windowClass.lpfnWndProc = MainWindowProc;

    windowClass.cbClsExtra = 0;

    windowClass.cbWndExtra = 0;

    windowClass.hInstance = GetModuleHandleA(NULL);

    windowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);

    windowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);

    windowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);

    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    windowClass.lpszMenuName = NULL;

    windowClass.lpszClassName = GAME_NAME "_WINDOWCLASS";



    if (!RegisterClassExA(&windowClass))
    {
        result = GetLastError();

        MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        goto Exit;
    }


    windowHandle = CreateWindowExA(WS_EX_CLIENTEDGE, windowClass.lpszClassName, "Window Title", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, GetModuleHandleA(NULL), NULL);


    if (!windowHandle)
    {
        result = GetLastError();
        MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        goto Exit;
    }

Exit:

    return(result);
}

BOOL GameIsAlreadyRunning(void)
{
    HANDLE mutex = NULL;

    mutex = CreateMutexA(NULL, FALSE, GAME_NAME "_Mutex");

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        return(TRUE);
    }
    else
    {
        return(FALSE);
    }
}