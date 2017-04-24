#include "board.h"

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
			this->spaces.push_space(&new_space);
		}
	}
}