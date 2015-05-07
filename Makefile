CFLAGS=-Weverything

graph: ; clang -o resistors-exe -O3 graph.c random64.c
