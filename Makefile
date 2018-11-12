all: library test
	gcc -Wall main.o scanUser.o modifyTrajectoire.o convertToFile.o newTrajectoire.o plotTrajectoire.o fgetTrajectoire.o -o projet
	./projet
test:library
	gcc -Wall -c main.c -o main.o
library:
	gcc -Wall -c scanUser.c -o scanUser.o 
	gcc -Wall -c modifyTrajectoire.c -o modifyTrajectoire.o
	gcc -Wall -c convertToFile.c -o convertToFile.o
	gcc -Wall -c newTrajectoire.c -o newTrajectoire.o
	gcc -Wall -c plotTrajectoire.c -o plotTrajectoire.o
	gcc -Wall -c fgetTrajectoire.c -o fgetTrajectoire.o