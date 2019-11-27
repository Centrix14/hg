#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "global_vars.h"
#include "coniox/coniox.h"

int is_valid_char(int c) {
	return (isprint(c) || isspace(c));
}

void ins(char *arg) {
	int c = 0, i = 0, pos = get_start_pos(), len = get_len();

	while (c != 27 && i < len) {
		if (is_valid_char(c)) {
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
