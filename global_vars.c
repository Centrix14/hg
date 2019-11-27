#define BUF_LEN 2048

int len = BUF_LEN, start_pos = 0;
char buffer[BUF_LEN];

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
