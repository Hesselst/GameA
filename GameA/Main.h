#pragma once

#define GAME_NAME "Game_A"

LRESULT CALLBACK MainWindowProc(_In_ HWND windowHandle, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam
);

DWORD CreateMainGameWindow(void);

BOOL GameIsAlreadyRunning(void);