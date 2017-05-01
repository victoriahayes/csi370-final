#ifndef _SPACE_H
#define _SPACE_H

#include <wchar.h>
#include <tchar.h>

/*
* Here, the properties of an individual space are defined.
*/

class Board_Space {
public:
	void init(int, int, int);
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
	int y;
	int index;
	int dis_value;
	bool flagged;
	bool hidden;
	bool bomb;
};

#endif //_SPACE_H