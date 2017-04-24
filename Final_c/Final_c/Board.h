#ifndef _BOARD_H
#define _BOARD_H

#include "LinkedList.h"
/*
 * Here, the properties of the game board are defined
 */

class Board {
	public:
		Board(int, int, int);
		~Board();
	private:
		void fill_list();
		int x;
		int y;
		int mines;
		LinkedList spaces;
};

#endif //_BOARD_H