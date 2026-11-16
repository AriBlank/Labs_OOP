#include "utils.h"

void UpdateMainText(HWND hMain, const std::wstring& text)
{
    SendMessage(hMain, WM_APP_UPDATE_TEXT, 0, (LPARAM)&text);
}