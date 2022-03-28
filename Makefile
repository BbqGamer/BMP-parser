run:
	g++ utils.c bmp.c -Wall -Wextra -o program
	./program

test:
	g++ utils.c bmp.c -Wall -Wextra -o program
	valgrind --tool=memcheck --leak-check=yes ./program