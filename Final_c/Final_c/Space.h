#ifndef _SPACE_H
#define _SPACE_H

/*
 * Here, the properties of an individual space are defined.
 */

class Board_Space {
	public:
		Board_Space(int, int);
		~Board_Space();
		void make_visible();
		void set_dis_value(int);
		void set_bomb();
		int get_x();
		int get_y();
		int get_data();
	private:
		int x;
		int y;
		bool bomb;
		int dis_value;
		bool hidden;
};

#endif //_SPACE_H