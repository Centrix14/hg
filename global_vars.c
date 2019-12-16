#include <stdio.h>
#include <stdlib.h>

#define BUF_LEN 1048576
#define INL_MAX 265

int len = BUF_LEN, start_pos = 0;
char sbuf[BUF_LEN];
char *dbuf, *buffer;
int inl_indexes[INL_MAX];
char inl_strs[INL_MAX][256];
int inl_count = 0;
int arr_pos = 0;

int get_start_pos() {
	return start_pos;
}

void set_start_pos(int val) {
	start_pos = val;
}

char *get_buffer() {
	return buffer;
}

int get_buffer_c(int buf_index) {
	return buffer[buf_index];
}

void set_buffer_c(int buf_index, int c) {
	buffer[buf_index] = c;
}

int get_len() {
	return len;
}

void set_len(int val) {
	len = val;
}

int get_buf_len() {
	return BUF_LEN;
}

int init_dbuf(int size) {
	dbuf = (char*)malloc(size);

	if (dbuf == NULL)
		return -1;
	return 0;
}

void use_dbuf(int is_true) {
	if (is_true) 
		buffer = dbuf;
	else
		buffer = sbuf;
}

void free_buf() {
	if (buffer == dbuf) {
		free(dbuf);
		buffer = sbuf;
	}
}

char *get_inl_strs_elm(int elm) {
	return inl_strs[elm];
}

void inl_add(int index, char *str) {
	sprintf(inl_strs[arr_pos], "%s", str);
	inl_indexes[arr_pos++] = index;
}

int is_inl_here(int pos) {
	for (int i = 0; i < INL_MAX; i++)
		if (inl_indexes[i] == pos) return i;
	return -1;
}

void inl_init() {
	for (int i = 0; i < INL_MAX; i++) {
		inl_indexes[i] = -1;
	}
}
