CFLAGS=-Weverything

graph: ; clang -o graph-exe -O3 graph.c random64.c
