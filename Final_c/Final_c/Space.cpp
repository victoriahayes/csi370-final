#include "space.h"

Board_Space::Board_Space(int x, int y, int i) {
	this->x = x;
	this->y = y;
	this->index = i;
	this->bomb = 0;
	this->dis_value = 0;
	this->hidden = 1;
	this->flagged = 0;
}

Board_Space::Board_Space() {
	this->x = 0;
	this->y = 0;
	this->bomb = 0;
	this->dis_value = 0;
	this->hidden = 1;
	this->index = 0;
	this->flagged = 0;
}

Board_Space::~Board_Space() {
}

void Board_Space::make_visible() {
	this->hidden = 0;
}

void Board_Space::set_dis_value(int value) {
	this->dis_value = value;
}

bool Board_Space::get_bomb() {
	return this->bomb;
}

void Board_Space::set_index(int i) {
	this->index = i;
}

int Board_Space::get_index() {
	return this->index;
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

bool Board_Space::get_hidden() {
	return this->hidden;
}

int Board_Space::get_data() {
	if (!this->bomb) {
		return this->dis_value;
	}
	else {
		return -1;
	}
}

bool Board_Space::get_flagged() {
	return this->flagged;
}

void Board_Space::toggle_flagged() {
	if (this->flagged) {
		this->flagged = false;
	}
	else {
		this->flagged = true;
	}
}