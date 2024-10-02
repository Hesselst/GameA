#include <stdio.h>

#pragma warning(push, 0)
#pragma warning(disable:4668)
#pragma warning(disable:5105)
#include <windows.h>
#pragma warning(pop)

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
);

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previousInstance, _In_ LPSTR cmdLine, _In_ int showCmd)
{

    UNREFERENCED_PARAMETER(previousInstance);

    UNREFERENCED_PARAMETER(cmdLine);

    UNREFERENCED_PARAMETER(showCmd);
    
    WNDCLASSEXA windowClass = { 0 };

    HWND windowHandle = { 0 };



    windowClass.cbSize = sizeof(WNDCLASSEXA);

    windowClass.style = 0;

    windowClass.lpfnWndProc = MainWindowProc;

    windowClass.cbClsExtra = 0;

    windowClass.cbWndExtra = 0;

    windowClass.hInstance = instance;

    windowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);

    windowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);

    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    windowClass.lpszMenuName = NULL;

    windowClass.lpszClassName = "GAME_A_WINDOWCLASS";

    windowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);


    if (!RegisterClassExA(&windowClass))
    {
        MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    windowHandle = CreateWindowExA(WS_EX_CLIENTEDGE, windowClass.lpszClassName, "Window Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, instance, NULL);

    if (!windowHandle)
    {
        MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    MSG message = { 0 };

    while (GetMessageA(&message, NULL, 0, 0) > 0)
    {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }

    return 0;
}

LRESULT CALLBACK MainWindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{

    switch (uMsg)
    {
        case WM_CREATE:
            // Initialize the window
            return 0;
        case WM_PAINT:
            // Paint the window's client area
            return 0;
        case WM_SIZE:
            // Set the size and position of the window
            return 0;
        case WM_DESTROY:
            // Clean up window specific data objects
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}