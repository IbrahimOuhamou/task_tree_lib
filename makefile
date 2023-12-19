#بسم الله الرحمن الرحيم


all:
	gcc -c src/ttree/ttree.c  -o bin/ttree.o
	gcc -c src/task_t.c  -o bin/task_t.o
	ar rcs bin/task_tree_lib.a bin/task_t.o bin/ttree.o
	gcc -r src/ttree/ttree.c src/task_t.c -o bin/task_tree_lib.o
	rm bin/task_t.o bin/ttree.o

