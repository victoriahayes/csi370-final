#ifndef _HEADER_H
#define _HEADER_H

#include <wchar.h>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <windowsx.h>

using namespace std;

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

struct Board_Space {
	int x,
		y,
		index,
		dis_value;
	bool flagged,
		hidden,
		bomb;
};

struct Board {
	int width,
		height,
		size,
		mines,
		remaining;
	Board_Space* spaces;
};

void destroy_start_screen();
void reveal(Board*, int);
void write_mine_values(Board_Space*, int);

Board_Space* init_board_space(int, int, int);
void make_visible(Board_Space*);
void set_dis_value(Board_Space*, int);
bool get_bomb(Board_Space*);
void set_index(Board_Space*, int);
int get_index(Board_Space*);
void set_bomb(Board_Space*);
int get_x(Board_Space*);
int get_y(Board_Space*);
bool get_hidden(Board_Space*);
int get_data(Board_Space*);

Board* Create_Board(int, int, int);
int get_width(Board*);
int get_height(Board*);
int get_remaining(Board*);
void shrink_remaining(Board*);
Board_Space* get_spaces(Board*);
Board_Space* fill_list(Board*);
int ** find_neighbors(Board*, int,int);
bool in_neighborhood(int**, int, int);
void calculate_dis_values(Board*);
Board_Space* find_at_location(Board*, int, int);
int get_mines(Board* game);
void gen_mines(Board*, int);

#endif