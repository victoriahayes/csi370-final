#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "Space.h"
#include <iostream>

using namespace std;

struct Node {
	Board_Space space;
	Node *next;
};

class LinkedList {
	public:
		LinkedList();
		~LinkedList();
		Node* get_head();
		void push_space(Board_Space);
		Board_Space* find_at_location(int, int);
		void print_list();
	private:
		Node* head;
};

#endif //_LINKED_LIST_H
