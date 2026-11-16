#include "module2.h"
#include "utils.h"
#include <string>

namespace {

HWND g_hEdit = nullptr;
HWND g_hDlg  = nullptr;

LRESULT CALLBACK Dialogue2Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        HINSTANCE hInst = GetModuleHandleW(nullptr);

        g_hEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            10, 20, 280, 24,
            hwnd, (HMENU)300, hInst, nullptr);

        CreateWindowW(L"BUTTON", L"Так",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            70, 70, 90, 30, hwnd, (HMENU)1, hInst, nullptr);

        CreateWindowW(L"BUTTON", L"Відміна",
            WS_CHILD | WS_VISIBLE,
            180, 70, 90, 30, hwnd, (HMENU)2, hInst, nullptr);

        SetFocus(g_hEdit);
        return 0;
    }

    case WM_COMMAND:
        switch (LOWORD(wp))
        {
        case 1:
        {
            int len = GetWindowTextLengthW(g_hEdit);
            std::wstring text(len, L'\0');
            GetWindowTextW(g_hEdit, &text[0], len + 1);
            UpdateMainText(GetParent(hwnd), text);
            DestroyWindow(hwnd);
            return 0;
        }
        case 2:
            DestroyWindow(hwnd);
            return 0;
        }
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

}

void ShowDialogB2(HWND hParent)
{
    static bool reg = false;
    const wchar_t* CLS = L"Dialogue2";

    if (!reg)
    {
        WNDCLASSW wc = {};
        wc.lpfnWndProc   = Dialogue2Proc;
        wc.hInstance     = GetModuleHandleW(nullptr);
        wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
        wc.lpszClassName = CLS;
        RegisterClassW(&wc);
        reg = true;
    }

    EnableWindow(hParent, FALSE);

    g_hDlg = CreateWindowW(CLS, L"введення тексту",
        WS_POPUP | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 320, 160,
        hParent, nullptr, GetModuleHandleW(nullptr), nullptr);

    ShowWindow(g_hDlg, SW_SHOW);
    UpdateWindow(g_hDlg);

    MSG msg;
    while (IsWindow(g_hDlg) && GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    EnableWindow(hParent, TRUE);
    SetActiveWindow(hParent);
}