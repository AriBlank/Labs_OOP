#include "module1.h"
#include "utils.h"
#include <string>

namespace {
    const wchar_t* GROUPS[] = {
        L"ІМ-51", L"ІМ-52", L"ІМ-53",
        L"ІМ-54",  L"ІМ-55",  L"ІМ-о51",
    };

    HWND g_hList = nullptr;
    HWND g_hDlg  = nullptr;

    LRESULT CALLBACK Dialogue1Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        switch (msg)
        {
        case WM_CREATE:
        {
            HINSTANCE hInst = GetModuleHandleW(nullptr);

            g_hList = CreateWindowW(L"LISTBOX", nullptr,
                WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY,
                10, 10, 280, 200,
                hwnd, (HMENU)100, hInst, nullptr);

            for (int i = 0; i < _countof(GROUPS); ++i)
                SendMessageW(g_hList, LB_ADDSTRING, 0, (LPARAM)GROUPS[i]);

            CreateWindowW(L"BUTTON", L"Так",
                WS_CHILD | WS_VISIBLE,
                70, 225, 90, 30, hwnd, (HMENU)1, hInst, nullptr);

            CreateWindowW(L"BUTTON", L"Відміна",
                WS_CHILD | WS_VISIBLE,
                180, 225, 90, 30, hwnd, (HMENU)2, hInst, nullptr);
            return 0;
        }

        case WM_COMMAND:
            switch (LOWORD(wp))
            {
            case 1: //кнопка так
            {
                int selected_index = (int)SendMessageW(g_hList, LB_GETCURSEL, 0, 0);
                if (selected_index != LB_ERR)
                {
                    wchar_t buf[256] = {};
                    SendMessageW(g_hList, LB_GETTEXT, selected_index, (LPARAM)buf);
                    UpdateMainText(GetParent(hwnd), buf); 
                }
                DestroyWindow(hwnd);
                return 0;
            }
            case 2: //кнопка отмена
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

void ShowDialogB1(HWND hParent)
{
    static bool reg = false;
    const wchar_t* CLS = L"Dialog1";

    if (!reg)
    {
        WNDCLASSW wc = {};
        wc.lpfnWndProc   = Dialogue1Proc;
        wc.hInstance     = GetModuleHandleW(nullptr);
        wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
        wc.lpszClassName = CLS;
        RegisterClassW(&wc);
        reg = true;
    }

    EnableWindow(hParent, FALSE);

    g_hDlg = CreateWindowW(CLS, L"вибір групи",
        WS_POPUP | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 320, 310,
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