#specify compilation settings
CC=g++
FLAGS = -I  -Wall --static

#specify targets
default: project

#main loop object file
main.o: project.cpp
	$(CC) $(FLAGS) -o main.o -c project.cpp
objects.o: lib/objects.cpp lib/objects.h
	$(CC) $(FLAGS) -c lib/objects.cpp
tests.o: lib/unit_tests.cpp
	$(CC) $(FLAGS) -o tests.o -c lib/unit_tests.cpp

#target
project: main.o objects.o tests.o
	$(CC) $(FLAGS) -o run main.o objects.o tests.o
	$(RM) *.o *~
	clear
	@echo "\n       HOSPITAL  PROJECT"
	@echo "(C) Artur Sebastian Miller 2021\n"
	@echo "has been successfully compiled!\n"
run: project
	clear
	./run
log: project
	./run >> log.txt
clean:
	$(RM) *.o *~
