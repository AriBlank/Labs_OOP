#include <windows.h>
#include <string>
#include "module1.h"
#include "module2.h"
#include "utils.h"

static HWND g_hStatic = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
        g_hStatic = CreateWindowW(L"STATIC", L"",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            10, 10, 400, 300,
            hwnd, nullptr, GetModuleHandle(nullptr), nullptr);
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wp))
        {
        case 1001: ShowDialogB1(hwnd); return 0;
        case 1002: ShowDialogB2(hwnd); return 0;
        case 1003: DestroyWindow(hwnd); return 0;
        }
        return 0;
    case WM_APP_UPDATE_TEXT:
    {
        const std::wstring* p = reinterpret_cast<const std::wstring*>(lp);
        SetWindowTextW(g_hStatic, p->c_str());
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}


int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int nCmdShow)
{
    HMENU hMenu = CreateMenu();
    AppendMenuW(hMenu, MF_STRING, 1001, L"Робота1");
    AppendMenuW(hMenu, MF_STRING, 1002, L"Робота2");
    AppendMenuW(hMenu, MF_STRING, 1003, L"Вихід");

    WNDCLASSW wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"Lab1";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowW(L"Lab1", L"1 лаба",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 
        CW_USEDEFAULT, CW_USEDEFAULT, 520, 400,
        nullptr, hMenu, hInst, nullptr);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}