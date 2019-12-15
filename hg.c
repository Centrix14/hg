/*
 * hg -- Hydrargyrum command console text editor
 * v0.9
 * 06.12.2019
 * by Centrix
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "global_vars.h"
#include "funcs.h"

#define LEN 17

int find(char *arr[], char *obj, int len);

int main(void) {
	char *cmnds[] = {"ins", "info", "help", "pr", "reg", "wr", "ld", "fill", "rub", "gt", "add", "pra", "hv", "ldb", "seb", "seek", "sel"};
	void (*funcs[])(char *arg) = {ins, info, help, pr, reg, wr, ld, fill, rub, gt, add, pra, hv, ldb, seb, seek, sel};
	char input[256] = "";
	char *tok;
	int is_cmnd = 0, arr_index = 0;

	tok = "";
	use_dbuf(0);
	setlocale(LC_ALL, " ");

	while (strcmp(input, "quit")) {
		is_cmnd = 1;
		
		tok = strtok(input, " ");
		while (tok != NULL) {
			if (is_cmnd) {
				arr_index = find(cmnds, input, LEN);

				if (arr_index >= 0) {
					(*funcs[arr_index])(tok);
					is_cmnd = 0;
				}
				else {
					fprintf(stderr, "it is no command `%s`\n", tok);
				}
			}
			else
				(*funcs[arr_index])(tok);

			tok = strtok(NULL, " ");
		}

		printf("hg> ");
		gets(input);
	}

	free_buf();
	return 0;
}

int find(char *arr[], char *obj, int len) {
	for (int i = 0; i < len; i++) {
		if (!strcmp(arr[i], obj)) return i;
	}
	return -1;
}
