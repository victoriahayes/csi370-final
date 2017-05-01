#ifndef _HEADER_H
#define _HEADER_H

#include "Board.h"

#include <wchar.h>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>

using namespace std;

/* The goal of this first build is to get the basics of this project running in c++
*/
void destroy_start_screen();
void reveal(int);
void write_mine_values(Board_Space* space, int index);

Board game;

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
#define EASY_X 9
#define EASY_Y 9
#define EASY_MINES 10

#define MEDIUM_X 16
#define MEDIUM_Y 16
#define MEDIUM_MINES 40

#define EXPERT_X 30
#define EXPERT_Y 16
#define EXPERT_MINES 99

#endif //_HEADER_H