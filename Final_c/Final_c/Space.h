#ifndef _SPACE_H
#define _SPACE_H

#include <wchar.h>
#include <tchar.h>

/*
 * Here, the properties of an individual space are defined.
 */

class Board_Space {
	public:
		Board_Space(int, int, int);
		Board_Space();
		~Board_Space();
		void make_visible();
		void set_dis_value(int);
		void set_bomb();
		void set_index(int);
		bool get_hidden();
		int get_index();
		int get_x();
		int get_y();
		bool get_flagged();
		void toggle_flagged();
		int get_data();
		bool get_bomb();
	private:
		int x;
		int index;
		int y;
		bool flagged;
		bool bomb;
		int dis_value;
		bool hidden;
};

#endif //_SPACE_H