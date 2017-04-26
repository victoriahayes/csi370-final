#include "LinkedList.h"

LinkedList::LinkedList() {
	head = nullptr;
}

LinkedList::~LinkedList() {
	Node* current = this->head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
}

Node* LinkedList::get_head() {
	return this->head;
}

void LinkedList::push_space(Board_Space space) {
	Node* new_node = new Node;
	new_node->space = space;
	new_node->next = nullptr;

	
	if (!this->head ) {
		this->head = new_node;
	}
	else {
		Node* p = this->head;
		while (p->next)
			p = p->next;
		p->next = new_node;
	}
}

Board_Space* LinkedList::find_at_location(int x, int y) {
	Node* searchNode = this->head;

	while (searchNode != nullptr) {
		if (searchNode->space.get_x() == x) {
			if (searchNode->space.get_y() == y) {
				return &searchNode->space;
			}
		}
		searchNode = searchNode->next;
	}
	return nullptr;
}

void LinkedList::print_list() {
	Node* searchNode = this->head;
	while (searchNode != nullptr) {
		cout << "( " << searchNode->space.get_x() << ", " <<
			searchNode->space.get_y() << " ) -> " << 
			searchNode->space.get_data()<<endl;
		searchNode = searchNode->next;
	}
}