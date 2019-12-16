/*
 * hg -- Hydrargyrum command console text editor
 * v1.0
 * 16.12.2019
 * by Centrix
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "global_vars.h"
#include "funcs.h"

#define LEN 18

int find(char *arr[], char *obj, int len);

int main(void) {
	char *cmnds[] = {"ins", "info", "help", "pr", "reg", "wr", "ld", "fill", "rub", "gt", "add", "pra", "hv", "ldb", "seb", "seek", "sel", "inl"};
	void (*funcs[])(char *arg) = {ins, info, help, pr, reg, wr, ld, fill, rub, gt, add, pra, hv, ldb, seb, seek, sel, inl};
	char input[256] = "";
	char *tok;
	int is_cmnd = 0, arr_index = 0;

	tok = "";
	inl_init();
	use_dbuf(0);
	setlocale(LC_ALL, " ");

	printf("-- hg code editor v1.0 16/12/2019 by Centrix\n   Type `help` for help\n\n");

	while (strcmp(input, "quit")) {
		is_cmnd = 1;
		
		tok = strtok(input, " \n");
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

			tok = strtok(NULL, " \n");
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
