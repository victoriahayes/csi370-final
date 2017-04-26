#include "header.h"

int main() {
	Board main_board(easy_x, easy_y, easy_mines);
	main_board.gen_mines(6, 3);
	system("Pause");
	return 0;
}