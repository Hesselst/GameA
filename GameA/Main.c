#include <stdio.h>

#pragma warning(push, 3)
#pragma warning(disable:4668)
#pragma warning(disable:5105)
#include <windows.h>
#pragma warning(pop)

#include "Main.h"

BOOL gGameIsRunning;

HWND gGameWindow;

GAMEBITMAP gDrawingSurface = { 0 };

int WINAPI __stdcall WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previousInstance, _In_ LPSTR cmdLine, _In_ int showCmd)
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

    gDrawingSurface.bitmapInfo.bmiHeader.biSize = sizeof(gDrawingSurface.bitmapInfo.bmiHeader);

    gDrawingSurface.bitmapInfo.bmiHeader.biWidth = GAME_RES_WIDTH;

    gDrawingSurface.bitmapInfo.bmiHeader.biHeight = GAME_RES_HEIGHT;

    gDrawingSurface.bitmapInfo.bmiHeader.biBitCount = GAME_BPP;

    gDrawingSurface.bitmapInfo.bmiHeader.biCompression = BI_RGB;

    gDrawingSurface.bitmapInfo.bmiHeader.biPlanes = 1;
    gDrawingSurface.memory = VirtualAlloc(NULL, GAME_DRAWING_AREA_MEMORY_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (gDrawingSurface.memory == NULL)
        {
            MessageBoxA(NULL, "Failed to allocate memory for drawing surface!", "Error!", MB_ICONEXCLAMATION | MB_OK);

            goto Exit;
         }

    MSG message = { 0 };

    gGameIsRunning = TRUE;
    while (gGameIsRunning == TRUE)
    {
        while (PeekMessageA(&message, gGameWindow, 0, 0, PM_REMOVE))
        {
            DispatchMessageA(&message);
        }

        ProcessPlayerInput();

        RenderFrameGraphics();

        Sleep(1);
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
            gGameIsRunning = FALSE;

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


    gGameWindow = CreateWindowExA(WS_EX_CLIENTEDGE, windowClass.lpszClassName, "Window Title", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, GetModuleHandleA(NULL), NULL);


    if (!gGameWindow)
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

void ProcessPlayerInput(void)
{
    short escapeKeyIsDown = GetAsyncKeyState(VK_ESCAPE);

    if (escapeKeyIsDown)
    {
        SendMessageA(gGameWindow, WM_CLOSE, 0, 0);
    }
}

void RenderFrameGraphics(void)
{

}