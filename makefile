SudokuPuzzle : main.o
	g++ main.o -o SudokuPuzzle
main.o : SudokuPuzzle.h main.cpp
	g++ -c main.cpp
clean :
	rm *.o
	rm SudokuPuzzle
	rm solved.txt
