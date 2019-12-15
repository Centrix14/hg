#include <stdlib.h>

#define BUF_LEN 1048576

int len = BUF_LEN, start_pos = 0;
char sbuf[BUF_LEN];
char *dbuf, *buffer;

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
