#include "header.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	
	int height = 200;
	int width = 300;

	WNDCLASSEX wcex;

	wcex.cbSize		   = sizeof(WNDCLASSEX);
	wcex.style		   = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = NULL;
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm       = NULL;

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("Failed to register project"),
			_T("Minesweeper Final Project"),
			NULL);

		return 1;
	}

	handle_main = hInstance;

	window = CreateWindow(szWindowClass, winTitle, 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
		width, height, NULL, NULL, hInstance, NULL);

	if (!window) {
		MessageBox(NULL, _T("Failed to Create Window"),
			_T("Minesweeper Final Project"), NULL);
		return 1;
	}

	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (start_screen) {
			screen_title = CreateWindowW(L"Static", L"Select Difficulty:", WS_CHILD | WS_VISIBLE,
				10, 10, 120, 30, hwnd, (HMENU)0, handle_main, NULL);
			easy_button = CreateWindowW(L"Button", L"Easy", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
				20, 30, 100, 30, hwnd, (HMENU)1, handle_main, NULL);
			medium_button = CreateWindowW(L"Button", L"Medium", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
				20, 55, 100, 30, hwnd, (HMENU)2, handle_main, NULL);
			hard_button = CreateWindowW(L"Button", L"Hard", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
				20, 80, 100, 30, hwnd, (HMENU)3, handle_main, NULL);
			start_button = CreateWindowW(L"Button", L"Start Game", WS_CHILD | WS_VISIBLE,
				150, 120, 100, 30, hwnd, (HMENU)4, handle_main, NULL);
			description = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE,
				150, 30, 120, 80, hwnd, NULL, handle_main, NULL);
		}
		else if (!first_click){
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			total = x*y;
			int i = 0;
			game_pieces = new HWND[total];
			while(i<total) {
				for (int j = 0; j < x; j++) {
					for (int k = 0; k < y; k++) {
						game_pieces[i] = CreateWindowW(L"Button", L" ", WS_CHILD | WS_VISIBLE,
							(20 * j), (20 * k), 20, 20, hwnd, (HMENU)i, handle_main, NULL);
						i++;
					}
				}
			}
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_CREATE:
		
		break;
	case WM_COMMAND:
		if(start_screen){
			if (HIWORD(wParam) == BN_CLICKED) {
				switch (LOWORD(wParam)) {
				case 1:
					mines = EASY_MINES;
					x = EASY_X;
					y = EASY_Y;
					SetWindowTextW(description, L"Mines: 10\nWidth: 9\nHeight: 9");
					can_continue = true;
					break;
				case 2:
					mines = MEDIUM_MINES;
					x = MEDIUM_X;
					y = MEDIUM_Y;
					SetWindowTextW(description, L"Mines: 40\nWidth: 16\nHeight: 16");
					can_continue = true;
					break;
				case 3:
					mines = EXPERT_MINES;
					x = EXPERT_X;
					y = EXPERT_Y;
					SetWindowTextW(description, L"Mines: 99\nWidth: 30\nHeight: 16");
					can_continue = true;
					break;
				case 4:
					if (can_continue) {
						start_screen = false;
						game.init(x, y, mines);
						destroy_start_screen();
						SetWindowPos(window, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, 25 * x, 25 * y, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_SHOWWINDOW);
						RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_NOFRAME | RDW_UPDATENOW);
					}
					break;
				default:
					break;
				}
			}
		}
		else {
			if (HIWORD(wParam) == BN_CLICKED) {
				int selected = LOWORD(wParam);
				if (!first_click) {
					game.gen_mines(selected);
					first_click = true;
				}
				reveal(selected);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;
	}
	return 0;
}

void reveal(int i) {
	int index = i;
	Board_Space* space = &game.get_spaces()[index];
	int y = space->get_y();
	int x = space->get_x();
	write_mine_values(space, index);
	if (space->get_hidden()) {
		space->make_visible();
		game.shrink_remaining();
	}
	if (game.get_remaining() == game.get_mines()) {
		MessageBox(NULL, _T("You Win!"), _T("Minsweeper Final Project"), NULL);
		PostQuitMessage(0);
	}
	int val = space->get_data();
	if (val == -1) {
		//game is over
		MessageBox(NULL,
			_T("Game Over"),
			_T("Minesweeper Final Project"),
			NULL);
		PostQuitMessage(0);
	}
	else if (val == 0) {
		//space is null, so its neighbors may be revealed as well
		int k = 1;
		int x = 0;
		int y = 0;
		int** neighbors = game.find_neighbors(space->get_x(), space->get_y());
		while (k < 9) {
			x = neighbors[k][0];
			y = neighbors[k][1];
			if (x >= 0 && x < game.get_x() && y >= 0 && game.get_y()) {
				Board_Space* tmp_space = game.find_at_location(x, y);
				if (tmp_space != nullptr) {
					if (tmp_space->get_hidden()) {
						reveal(tmp_space->get_index());
					}
				}
			}
			k++;
		}
	}
}

void write_mine_values(Board_Space* space, int index) {
		switch (space->get_data()) {
		case 0:
			SetWindowTextW(game_pieces[index], L" ");
			break;
		case 1:
			SetWindowTextW(game_pieces[index], L"1");
			break;
		case 2:
			SetWindowTextW(game_pieces[index], L"2");
			break;
		case 3:
			SetWindowTextW(game_pieces[index], L"3");
			break;
		case 4:
			SetWindowTextW(game_pieces[index], L"4");
			break;
		case 5:
			SetWindowTextW(game_pieces[index], L"5");
			break;
		case 6:
			SetWindowTextW(game_pieces[index], L"6");
			break;
		case 7:
			SetWindowTextW(game_pieces[index], L"7");
			break;
		case 8:
			SetWindowTextW(game_pieces[index], L"8");
			break;
		case -1:
			SetWindowTextW(game_pieces[index], L"X");
			break;
		default:
			break;
		}
		Button_SetState(game_pieces[index], true);
	Button_Enable(game_pieces[index], false);
}

void destroy_start_screen() {
	/*
	 * Clears all child elelments from the window
	 */
	DestroyWindow(screen_title);
	DestroyWindow(easy_button);
	DestroyWindow(medium_button);
	DestroyWindow(hard_button);
	DestroyWindow(start_button);
	DestroyWindow(description);
}