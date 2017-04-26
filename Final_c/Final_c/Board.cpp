#include "board.h"
using namespace std;

Board::Board(int x, int y, int mines) {
	this->x = x;
	this->y = y;
	this->mines = mines;
	fill_list();
}

Board::~Board(){}

void Board::fill_list() {
	for (int i = 0; i < this->x; i++) {
		for (int j = 0; j < this->y; j++) {
			Board_Space new_space = Board_Space(i, j);
			this->spaces.push_space(new_space);
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
	Board_Space* space = new Board_Space();

	for (int i = 0; i < this->x; i++) {
		for (int j = 0; j < this->y; j++) {
			danger = 0;
			neighbors = this->find_neighbors(i, j);
			for (int k = 0; k < 9; k++) {
				if (k == 0) {
					space = this->spaces.find_at_location(neighbors[k][0], neighbors[k][1]);
					if (space->get_bomb()) {
						k = 10;
						break;
					}
				}
					if (this->spaces.find_at_location(neighbors[k][0], neighbors[k][1])) {
						if(this->spaces.find_at_location(neighbors[k][0], neighbors[k][1])->get_bomb())
							danger++;
				}
			}
			space->set_dis_value(danger);
		}
	}
	this->spaces.print_list();
}

void Board::gen_mines(int x, int y) {
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
			Board_Space * space = this->spaces.find_at_location(tmp_x, tmp_y);
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
