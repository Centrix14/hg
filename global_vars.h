#ifndef __HG_EDITOR_GLOBAL_VARS_H_INCLUDED__
#define __HG_EDITOR_GLOBAL_VARS_H_INCLUDED__

int get_start_pos();
void set_start_pos(int val);

char *get_buffer();
int get_buffer_c(int buf_index);
void set_buffer_c(int buf_index, int c);

int get_len();
void set_len(int val);

#endif
