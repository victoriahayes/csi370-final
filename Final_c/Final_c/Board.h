#ifndef _BOARD_H
#define _BOARD_H

#include <time.h>

#include "LinkedList.h"
/*
 * Here, the properties of the game board are defined
 */

class Board {
	public:
		Board(int, int, int);
		void gen_mines(int, int);
		~Board();
	private:
		void fill_list();
		int** find_neighbors(int, int);
		bool in_neighborhood(int**, int, int);
		void calculate_dis_values();
		int x;
		int y;
		int mines;
		LinkedList spaces;
};

#endif //_BOARD_H