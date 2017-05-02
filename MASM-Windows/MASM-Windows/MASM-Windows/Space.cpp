#include "space.h"

void Board_Space::init(int x, int y, int i) {
	__asm { mov eax, dword ptr[this]
			mov ecx, dword ptr[x]
			mov dword ptr[eax], ecx			//x
			mov ecx, dword ptr[y]
			mov dword ptr[eax + 4], ecx     //y
			mov ecx, dword ptr[i]
			mov dword ptr[eax + 8], ecx		//i
			mov dword ptr[eax + 12], 0		//dis_value
			mov byte ptr[eax + 16], 0		//flagged
			mov byte ptr[eax + 17], 1		//hidden
			mov byte ptr[eax + 18], 0		//bomb
	};
}

Board_Space::Board_Space() {
	__asm { mov eax, dword ptr[this]
		mov dword ptr[eax], 0				//x
		mov dword ptr[eax + 4], 0			//y
		mov dword ptr[eax + 8], 0			//index
		mov dword ptr[eax + 12], 0			//dis_value
		mov byte ptr[eax + 16], 0			//flagged
		mov byte ptr[eax + 17], 1			//hidden
		mov byte ptr[eax + 18], 0			//bomb
	};
}

Board_Space::~Board_Space() {
}

void Board_Space::make_visible() {
	__asm { mov eax, dword ptr[this]
		mov byte ptr[eax + 17], 0
	};
}

void Board_Space::set_dis_value(int value) {
	__asm { mov eax, dword ptr[this]
		mov ecx, dword ptr[value]
		mov dword ptr[eax + 12], ecx
	};
}

bool Board_Space::get_bomb() {
	__asm { mov eax, dword ptr[this]
		mov al, byte ptr[eax+18]
	};
}

void Board_Space::set_index(int i) {
	__asm {mov eax, dword ptr[this]
		mov ecx, dword ptr[i]
		mov dword ptr[eax + 8], ecx
	};
}

int Board_Space::get_index() {
	__asm {mov eax, dword ptr[this]
		mov eax, dword ptr[eax + 8]
	};
}

void Board_Space::set_bomb() {
	__asm { mov eax, dword ptr[this]
		mov byte ptr[eax + 18], 1
	};
}

int Board_Space::get_x() {
	__asm {mov eax, dword ptr[this]
		mov eax, dword ptr[eax]
	};
}

int Board_Space::get_y() {
	__asm {mov eax, dword ptr[this]
		mov eax, dword ptr[eax + 4]
	};
}

bool Board_Space::get_hidden() {
	__asm {mov eax, dword ptr[this]
		mov al, byte ptr[eax + 17]
	};
}

int Board_Space::get_data() {
	// return -1 if the space is a bomb,
	// otherwise returns the number of bombs neighboring the space
	__asm { mov eax, dword ptr[this]
		mov cl, byte ptr[eax + 18]
		mov dl, 0
		cmp cl, dl
		je ret_dis_value
		mov edx, -1
		jmp finish_comp
		ret_dis_value :
	mov edx, dword ptr[eax + 12]
		finish_comp :
		mov eax, edx
	};
}

bool Board_Space::get_flagged() {
	__asm { mov eax, dword ptr[this]
		mov cl, byte ptr[eax + 16]
		xor eax, eax
		mov al, cl
	};
}

void Board_Space::toggle_flagged() {
	__asm { mov eax, dword ptr[this]
		mov cl, byte ptr[eax + 16]
		mov edx, 1
		xor ecx, edx
		mov byte ptr[eax + 16], cl
	};
}