#ifndef _HEADER_H
#define _HEADER_H

#include "Board.h"
#include "MajorVars.h"

using namespace std;

/* The goal of this first build is to get the basics of this project running in c++
*/
void destroy_start_screen();
void reveal(int);
void write_mine_values(Board_Space* space, int index);

Board game;

#define EASY_X 9
#define EASY_Y 9
#define EASY_MINES 10

#define MEDIUM_X 16
#define MEDIUM_Y 16
#define MEDIUM_MINES 40

#define EXPERT_X 30
#define EXPERT_Y 16
#define EXPERT_MINES 99

#endif //_HEADER_H