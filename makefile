#بسم الله الرحمن الرحيم


all:
	gcc -c src/tlist/tlist.c  -o bin/tlist.o
	gcc -c src/task_t.c  -o bin/task_t.o
	ar rcs bin/task_tree_lib.a bin/task_t.o bin/tlist.o
	gcc -r src/tlist/tlist.c src/task_t.c -o bin/task_tree_lib.o
	rm bin/task_t.o bin/tlist.o

