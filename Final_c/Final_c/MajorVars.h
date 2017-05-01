#ifndef _MAJOR_VARS_H
#define _MAJOR_VARS_H

#include <wchar.h>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>

static HWND screen_title,
	easy_button,
	medium_button,
	title_name,
	hard_button,
	start_button,
	description;

HWND* game_pieces;

PAINTSTRUCT ps;
HDC hdc;

static TCHAR szWindowClass[] = _T("MinesweeperFinalProject");
static TCHAR winTitle[] = _T("Minesweeper");

int mines = 0, x = 0, y = 0, total = 0;

bool start_screen = true;
bool can_continue = false;
bool first_click = false;

RECT mRect;
const wchar_t *difficulties[] = { L"Easy", L"Medium", L"Hard" };

HINSTANCE handle_main;
HWND window;

#endif //_MAJOR_VARS_H