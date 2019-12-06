/*
 * hg -- Hydrargyrum command console text editor
 * v0.7
 * 06.12.2019
 * by Centrix
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "global_vars.h"
#include "funcs.h"

#define LEN 13

int find(char *arr[], char *obj, int len);

int main(void) {
	char *cmnds[] = {"ins", "info", "help", "pr", "reg", "wr", "ld", "fill", "rub", "gt", "add", "pra", "hv"};
	void (*funcs[])(char *arg) = {ins, info, help, pr, reg, wr, ld, fill, rub, gt, add, pra, hv};
	char input[256] = "";
	char *tok;
	int is_cmnd = 0, arr_index = 0;

	tok = "";

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
	return 0;
}

int find(char *arr[], char *obj, int len) {
	for (int i = 0; i < len; i++) {
		if (!strcmp(arr[i], obj)) return i;
	}
	return -1;
}
