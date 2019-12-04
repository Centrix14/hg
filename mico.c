#include "mico.h"
#include "coniox/coniox.h"
#include <ctype.h>

int get_char_type(int c) {
	int (*funcs[])(int) = {isalpha, isdigit, ispunct};

	for (int i = 0; i < 3; i++) {
		if ((*funcs[i])(c)) return i;
	}

	return -1;
}

void hl(int c) {
	switch (get_char_type(c)) {
		case LETTER:
			setColor(BLACK, WHITE, BRIGHT);
		break;

		case DIGIT:
			setColor(BLACK, YELLOW, NORMAL);
		break;

		case PUNCT:
			setColor(BLACK, GREEN, BRIGHT);
		break;

		default:
			setColor(BLACK, BLACK, NORMAL);
		break;
	}
}
