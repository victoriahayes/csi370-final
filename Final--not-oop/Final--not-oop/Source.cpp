#include "header.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	int height = 200;
	int width = 300;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

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

	return (int)msg.wParam;
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
		else if (!first_click) {
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			total = x*y;
			int i = 0;
			game_pieces = new HWND[total];
			while (i<total) {
				for (int j = 0; j < x; j++) {
					for (int k = 0; k < y; k++) {
						game_pieces[i] = CreateWindowW(L"Button", L" ", WS_CHILD | WS_VISIBLE,
							(20 * k), (20 * j), 20, 20, hwnd, (HMENU)i, handle_main, NULL);
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
		if (start_screen) {
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

void reveal(Board* game, int i) {
	/*
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
					if (tmp_space->get_hidden() != 0) {
						reveal(tmp_space->get_index());
					}
				}
			}
			k++;
		}
	}*/
}

void write_mine_values(Board_Space* space, int index) {
	switch (get_data(space)) {
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

Board_Space* init_board_space(int x, int y, int i) {
	Board_Space space;
	__asm {
		mov eax, dword ptr[space]
		mov ecx, dword ptr[x]
		mov dword ptr[eax], ecx			//x
		mov ecx, dword ptr[y]
		mov dword ptr[eax + 4], ecx     //y
		mov ecx, dword ptr[i]
		mov dword ptr[eax + 8], ecx		//i
		mov dword ptr[eax + 12], 0		//dis_value
		mov byte ptr[eax + 16], 0		//flagged
		mov byte ptr[eax + 17], 1		//hidden
		mov byte ptr[eax + 18], 0		//bomb
	};
}

void make_visible(Board_Space* space) {
	__asm { mov eax, dword ptr[space]
		mov byte ptr[eax + 17], 0
	};
}

void set_dis_value(Board_Space* space, int value) {
	__asm { mov eax, dword ptr[space]
		mov ecx, dword ptr[value]
		mov dword ptr[eax + 12], ecx
	};
}

bool get_bomb(Board_Space* space) {
	__asm { mov eax, dword ptr[space]
		mov al, byte ptr[eax + 18]
	};
}

void set_index(Board_Space* space, int i) {
	__asm {mov eax, dword ptr[space]
		mov ecx, dword ptr[i]
		mov dword ptr[eax + 8], ecx
	};
}

int get_index(Board_Space* space) {
	__asm {mov eax, dword ptr[space]
		mov eax, dword ptr[eax + 8]
	};
}

void set_bomb(Board_Space* space) {
	__asm { mov eax, dword ptr[space]
		mov byte ptr[eax + 18], 1
	};
}

int get_x(Board_Space* space) {
	__asm {mov eax, dword ptr[space]
		mov eax, dword ptr[eax]
	};
}

int get_y(Board_Space* space) {
	__asm {mov eax, dword ptr[space]
		mov eax, dword ptr[eax + 4]
	};
}

bool get_hidden(Board_Space* space) {
	__asm {mov eax, dword ptr[space]
		mov al, byte ptr[eax + 17]
	};
}

int get_data(Board_Space* space) {
	// return -1 if the space is a bomb,
	// otherwise returns the number of bombs neighboring the space
	__asm { mov eax, dword ptr[space]
		mov cl, byte ptr[eax + 18]
		mov dl, 0
		cmp cl, dl
		je ret_dis_value
		mov edx, -1
		jmp finish_comp
		ret_dis_value :
	mov edx, dword ptr[eax + 12]
		finish_comp :
		mov eax, edx
	};
}

Board* Create_Board(int width, int height, int mines) {
	Board* game;
	__asm {
		mov eax, dword ptr[game]
			mov edx, dword ptr[width]
			mov dword ptr[eax], edx			//x
			mov ecx, dword ptr[height]
			mov dword ptr[eax + 4], ecx		//y
			mov esi, eax
			mov eax, ecx
			mul edx
			mov ecx, eax
			mov eax, esi
			mov dword ptr[eax + 8], ecx		//size (=x*y)
			mov dword ptr[eax + 16], ecx	//remaining (=size)
			mov ecx, dword ptr[mines]
			mov dword ptr[eax + 12], ecx	//mines
	};
	//this->spaces = new Board_Space[size];		//sparing my sanity and not doing object orientred assembly
	//fill_list();
}

int get_width(Board* game) {
	__asm {mov eax, dword ptr[game]
		mov eax, dword ptr[eax]
	}
}

int get_y(Board* game) {
	__asm {mov eax, dword ptr[game]
		mov eax, dword ptr[eax + 4]
	}
}

int get_remaining(Board* game) {
	__asm {mov eax, dword ptr[game]
		mov eax, dword ptr[eax + 16]
	}
}

void shrink_remaining(Board* game) {
	__asm {mov eax, dword ptr[game]
		mov ecx, dword ptr[eax + 16]
		dec ecx
		mov dword ptr[eax + 16], ecx
	}
}

Board_Space* get_spaces(Board* game) {
	__asm { mov eax, dword ptr[game]
		mov eax, dword ptr[eax + 20]
	};
}

Board_Space* fill_list(Board*) {
	//int k = 0;
	//for (int i = 0; i < this->x; i++) {
	//	for (int j = 0; j < this->y; j++) {
	//		Board_Space new_space;
	//		new_space.init(j, i, k);
	//		this->spaces[k] = new_space;
	//		k++;
	//	}
	//}
}

int** find_neighbors(Board* game,int x, int y) {
	int index = 0;
	int modifiers[3] = { 0, -1, 1 };
	int ** arr;
	arr = new int*[9];
	for (int i = 0; i < 9; i++) {
		arr[i] = new int[2];
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr[index][0] = x + modifiers[i];
			arr[index][1] = y + modifiers[j];
			index++;
		}
	}
	return arr;
}

bool in_neighborhood(int** neighbors, int x, int y) {
	for (int i = 0; i < 9; i++) {
		if (neighbors[i][0] == x) {
			if (neighbors[i][1] == y) {
				return true;
			}
		}
	}
	return false;
}

void calculate_dis_values(Board*) {
/*	int ** neighbors;
	int danger = 0;
	Board_Space* space = nullptr;

	for (int i = 0; i < this->x; i++) {
		for (int j = 0; j < this->y; j++) {
			danger = 0;
			neighbors = this->find_neighbors(i, j);
			for (int k = 0; k < 9; k++) {
				if (k == 0) {
					space = this->find_at_location(neighbors[k][0], neighbors[k][1]);
					if (space->get_bomb()) {
						k = 10;
						break;
					}
				}
				if (this->find_at_location(neighbors[k][0], neighbors[k][1])) {
					if (this->find_at_location(neighbors[k][0], neighbors[k][1])->get_bomb())
						danger++;
				}
			}
			space->set_dis_value(danger);
		}
	} */
}

Board_Space* find_at_location(Board* game, int x, int y) {
	/*for (int i = 0; i < this->size; i++) {
		if (this->spaces[i].get_x() == x) {
			if (this->spaces[i].get_y() == y) {
				return &this->spaces[i];
			}
		}
	}
	return nullptr;*/
}

int get_mines(Board* game) {
	__asm { mov eax, dword ptr[game]
		mov eax, [eax + 12]
	};
}

void gen_mines(Board* game, int i) {
/*	Board_Space* space = &this->spaces[i];
	int x = space->get_x();
	int y = space->get_y();
	int** neighbors = this->find_neighbors(x, y);
	int counter = 0;
	int tmp_x = 0;
	int tmp_y = 0;

	srand(time(NULL));

	while (counter < this->mines) {

		tmp_x = rand() % this->x;
		tmp_y = rand() % this->y;

		cout << "[ " << tmp_x << ", " << tmp_y << " ]\r\n";
		if (!in_neighborhood(neighbors, tmp_x, tmp_y)) {
			Board_Space * space = this->find_at_location(tmp_x, tmp_y);
			if (space) {
				if (!space->get_bomb()) {
					space->set_bomb();
					counter++;
				}
			}
		}
	}
	calculate_dis_values();*/
}
