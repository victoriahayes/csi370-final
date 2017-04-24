#include "space.h"

Board_Space::Board_Space(int x, int y) {
	this->x = x;
	this->y = y;
	this->bomb = 0;
	this->dis_value = 0;
	this->hidden = 1;
}

Board_Space::~Board_Space() {
}

void Board_Space::make_visible() {
	this->hidden = 1;
}

void Board_Space::set_dis_value(int value) {
	this->dis_value = value;
}

void Board_Space::set_bomb() {
	this->bomb = 1;
}

int Board_Space::get_x() {
	return this->x;
}

int Board_Space::get_y() {
	return this->y;
}

int Board_Space::get_data() {
	if (!this->bomb) {
		return this->dis_value;
	}
	else {
		return -1;
	}
}