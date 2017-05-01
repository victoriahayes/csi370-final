#include "board.h"

Board::Board() {
}

void Board::init(int x, int y, int mines) {
	this->x = x;
	this->y = y;
	this->size = x*y;
	this->mines = mines;
	this->remaining = this->size;
	this->spaces = new Board_Space[size];
	fill_list();
}

int Board::get_x() {
	return this->x;
}

int Board::get_y() {
	return this->y;
}

int Board::get_remaining() {
	return this->remaining;
}

void Board::shrink_remaining() {
	this->remaining--;
}

Board_Space* Board::get_spaces() {
	return this->spaces;
}

Board::~Board(){}

void Board::fill_list() {
	int k = 0;
	for (int i = 0; i < this->x; i++) {
		for (int j = 0; j < this->y; j++) {
			Board_Space new_space = Board_Space(i, j, k);
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

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr[index] = new int[2];
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
						if(this->find_at_location(neighbors[k][0], neighbors[k][1])->get_bomb())
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
	return this->mines;
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
