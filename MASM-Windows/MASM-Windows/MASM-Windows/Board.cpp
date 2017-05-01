#include "board.h"

Board::Board() {
	__asm {mov eax, dword ptr[this]
		mov dword ptr[eax], 0
		mov dword ptr[eax + 4], 0
		mov dword ptr[eax + 8], 0
		mov dword ptr[eax + 12], 0
		mov dword ptr[eax + 16], 0
		mov dword ptr[eax + 20], 0
	}
}

void Board::init(int x, int y, int mines) {
	__asm {
	mov eax, dword ptr[this]
		mov edx, dword ptr[x]
		mov dword ptr[eax], edx			//x
		mov ecx, dword ptr[y]
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
	this->spaces = new Board_Space[size];		//sparing my sanity and not doing object orientred assembly
	fill_list();
}

int Board::get_x() {
	__asm {mov eax, dword ptr[this]
		mov eax, dword ptr[eax]
	}
}

int Board::get_y() {
	__asm {mov eax, dword ptr[this]
		mov eax, dword ptr[eax + 4]
	}
}

int Board::get_remaining() {
	__asm {mov eax, dword ptr[this]
		mov eax, dword ptr[eax + 16]
	}
}

void Board::shrink_remaining() {
	__asm {mov eax, dword ptr[this]
		mov ecx, dword ptr[eax + 16]
		dec ecx
		mov dword ptr[eax + 16], ecx
	}
}

Board_Space* Board::get_spaces() {
	__asm { mov eax, dword ptr[this]
		mov eax, dword ptr[eax + 20]
	};
}

Board::~Board() {}

void Board::fill_list() {
	int k = 0;
	for (int i = 0; i < this->x; i++) {
		for (int j = 0; j < this->y; j++) {
			Board_Space new_space;
			new_space.init(j, i, k);
			this->spaces[k] = new_space;
			k++;
		}
	}
}

int** Board::find_neighbors(int x, int y) {
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

bool Board::in_neighborhood(int** neighbors, int x, int y) {
	for (int i = 0; i < 9; i++) {
		if (neighbors[i][0] == x) {
			if (neighbors[i][1] == y) {
				return true;
			}
		}
	}
	return false;
}

void Board::calculate_dis_values() {
	int ** neighbors;
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
	}
}

Board_Space* Board::find_at_location(int x, int y) {
	for (int i = 0; i < this->size; i++) {
		if (this->spaces[i].get_x() == x) {
			if (this->spaces[i].get_y() == y) {
				return &this->spaces[i];
			}
		}
	}
	return nullptr;
}

int Board::get_mines() {
	__asm { mov eax, dword ptr[this]
		mov eax, [eax + 12]
	};
}

void Board::gen_mines(int i) {
	Board_Space* space = &this->spaces[i];
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
	calculate_dis_values();
}
