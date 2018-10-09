play: game.o piece.o othello.o main.o
	g++ -o play game.o piece.o othello.o main.o
game.o: game.h game.cc
	g++ -c game.cc
piece.o: piece.h piece.cc
	g++ -c piece.cc
othello.o: othello.h othello.cc
	g++ -c othello.cc
main.o: main.cc
	g++ -c main.cc
