#ifndef _BOARD_H
#define _BOARD_H

#include <time.h>
#include <iostream>
using namespace std;

#include "Space.h"
/*
* Here, the properties of the game board are defined
*/

class Board {
public:
	Board();
	void init(int, int, int);
	void gen_mines(int);
	Board_Space* get_spaces();
	int** find_neighbors(int, int);
	bool in_neighborhood(int**, int, int);
	Board_Space* find_at_location(int, int);
	void fill_list();
	int get_x();
	int get_y();
	int get_mines();
	void calculate_dis_values();
	int get_remaining();
	void shrink_remaining();
	~Board();
private:
	int x;
	int y;
	int size;
	int mines;
	int remaining;
	Board_Space* spaces;
};

#endif //_BOARD_H