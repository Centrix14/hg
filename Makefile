all:
	gcc -O6 -o hg hg.c funcs.c coniox/libconiox.c global_vars.c mico.c
