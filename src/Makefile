run: main
	./main

main :
	gcc -o main os.c

gdb_main:
	gcc -g -ggdb3 -o main main.c
	gdb ./main

gdb_os:
	gcc -g -ggdb3 -o os os.c
	gdb ./os

# install ncurses library (for linux)
install:
	sudo apt-get install libncurses5-dev libncursesw5-dev
	
clean:
	rm -f main
	rm -f os
	rm -f keylogger
	rm -f *.o
	rm -f *.output
	rm -f *.exe
	rm -f *.txt
	clear
