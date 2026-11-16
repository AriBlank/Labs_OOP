#pragma once
#include <windows.h>
#include <string>

const UINT WM_APP_UPDATE_TEXT = WM_APP + 1;

void UpdateMainText(HWND hMain, const std::wstring& text);