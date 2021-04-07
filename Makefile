NAME=main

all: compiler

run: compiler
	./$(NAME).exe

compiler:
	g++ *.cpp -o $(NAME).exe

gdb:
	g++ -g *.cpp -o $(NAME).exe

clean:
	rm *.o *.exe
