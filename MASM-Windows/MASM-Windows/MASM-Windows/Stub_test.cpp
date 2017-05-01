/*#include "Space.h"

int main() {
	Board_Space test_space; //test null constructor
	Board_Space t_space;
	test_space.init(1, 2, 5); //test constructor
	t_space.init(2, 2, 6);

	test_space.make_visible();
	t_space.set_dis_value(3);
	int val = t_space.get_data();
	test_space.set_bomb();
	bool blah = test_space.get_bomb();
	blah = t_space.get_bomb();
	val = t_space.get_x();
	val = test_space.get_y();
	val = t_space.get_index();
	blah = test_space.get_flagged();
	test_space.toggle_flagged();
	blah = test_space.get_flagged();
	return 0;
}*/
/*
#include "Board.h"
#include "Space.h"

int main() {
	Board board;
	board.init(6, 7, 12);
	Board_Space* spaces = board.get_spaces();
	int blah = board.get_mines();
	blah = board.get_remaining();
	board.shrink_remaining();
	blah = board.get_remaining();
	return 0;
}*/