#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "global_vars.h"
#include "coniox/coniox.h"
#include "mico.h"

int is_valid_char(int c) {
	return (isprint(c) || isspace(c));
}

void ins(char *arg) {
	int c = 0, i = 0, pos = get_start_pos(), len = get_len();
	int line = 1;

	printf("1~ ");
	while (c != 27 && i < len) {
		if (is_valid_char(c) && c != 10) {
			putc(c, stdout);
			set_buffer_c(pos+i, c);
			i++;
		}
		else {
			switch (c) {
				case 8: ;
				case 127:
					if (i > 0) {
						i--;
						printf("\b \b");
						set_buffer_c(pos+i, 0);
					}
				break;
				case 10:
					set_buffer_c(pos+i, '\n');
					line++;
					i++;
					printf("\n%d~ ", line);
				break;
			}
		}
		
		c = readKb();
	}

	printf("\n\n*%d*\n", i);
}

void info(char *arg) {
	printf("-- info\n\tstart_pos = %d\n\tlen = %d\n", get_start_pos(), get_len());
}

void help(char *arg) {
	FILE *help_file = fopen("help", "r");
	int c = 0;
	
	c = getc(help_file);
	while ( !feof(help_file) && is_valid_char(c) ) {
		putc(c, stdout);
		c = getc(help_file);
	}

	fclose(help_file);
}

void pr(char *arg) {
	for (int i = 0; i < get_len(); i++) {
		putc(get_buffer_c(get_start_pos()+i), stdout);
	}
	printf("\n\nPrinted characters %d - %d\n", get_start_pos(), get_start_pos()+get_len());
}

void reg(char *arg) {
	static int state = 0;

	if (!strcmp(arg, "reg")) return;

	if (!state) {
		set_start_pos(atoi(arg));
	}
	else {
		set_len( atoi(arg) - get_start_pos() );
	}

	state = !state;
}

void wr(char *arg) {
	static int state = 0;
	FILE *dst;
	int i = 0;

	if (!state) {
		state = 1;
		return;
	}

	dst = fopen(arg, "w");

	if (dst == NULL) {
		fprintf(stderr, "The problem when writing the file `%s`\n", arg);
	}

	while ( is_valid_char(get_buffer_c(i)) ) {
		putc(get_buffer_c(i++), dst);
	}

	fclose(dst);

	state = 0;
}

void ld(char *arg) {
	static int state = 0;
	FILE *src;
	int i = 0, c = 0;

	if (!state) {
		state = 1;
		return;
	}

	src = fopen(arg, "r");

	if (src == NULL) {
		fprintf(stderr, "There is no such file `%s`\n", arg);
	}

	c = getc(src);
	while (!feof(src) && is_valid_char(c)) {
		set_buffer_c(i++, c);
		c = getc(src);
	}

	set_start_pos(0);
	set_len(i);

	fclose(src);

	state = 0;
}

void fill(char *arg) {
	static int state = 0;

	if (!state) {
		state = 1;
		return;
	}

	for (int i = 0; i < get_len(); i++) {
		set_buffer_c(get_start_pos()+i, arg[0]);
	}

	state = 0;
}

void rub(char *arg) {
	for (int i = 0; i < get_len(); i++) {
		set_buffer_c(get_start_pos()+i, ' ');
	}
}

void gt(char *arg) {
	char *args[] = {"start", "first", "last", "end"};
	enum argi {START, FIRST, LAST, END};
	static int state = 0;
	int i = 0, j = 0, arr_index = 0, out = 0;

	if (!state) {
		state = 1;
		return;
	}

	for (i = 0; i < 4; i++) {
		if (!strcmp(args[i], arg)) {
			arr_index = i;
			break;
		}
	}

	if (!arr_index && i) {
		fprintf(stderr, "unknown option `%s`\n", arg);
		return;
	}
	
	switch (arr_index) {
		case START: 
			set_start_pos(0);
		break;

		case FIRST:
			while (!is_valid_char(get_buffer_c(j))) j++;
			set_start_pos(j);
			out = j;
		break;

		case LAST:
			j = 0;
			while (is_valid_char(get_buffer_c(j))) j++;
			set_start_pos(j);
			out = j;
		break;

		case END:
		set_start_pos(get_buf_len());
		out = get_buf_len();
		break;
	}
	
	state = 0;

	printf("%d\n", out);
}

void add(char *arg) {
	int i = 0;

	while (is_valid_char(get_buffer_c(i))) i++;
	set_start_pos(i);
	set_len(get_buf_len()-i);

	ins("");
}

void pra(char *arg) {
	int c = 0, i = 0;
	int x = 0, y = 0;
	int line = 1;

	clean();

	printf("1~ ");
	while (is_valid_char(get_buffer_c(i))) {
		if (get_buffer_c(i) == '\n') {
			setColor(BLACK, WHITE, NORMAL);
			printf("\n%d~ ", line++);
		}

		else {
			hl(get_buffer_c(i));
			putc(get_buffer_c(i), stdout);
		}
		i++;
	}

	mvCursor(0, 0);

	while (c != 27) {
		switch (c) {
			case 'w': ;
			case 'k':
				y--;
				mvCursor(x, y);
			break;

			case 'a': ;
			case 'h':
				x--;
				mvCursor(x, y);
			break;

			case 's': ;
			case 'j':
				y++;
				mvCursor(x, y);
			break;

			case 'd': ;
			case 'l':
				x++;
				mvCursor(x, y);
			break;
		}

		c = readKb();
	}
	
	setColor(BLACK, WHITE, NORMAL);
	clean();
}
