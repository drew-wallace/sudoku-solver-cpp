#include <iostream>
#include "./SudokuPuzzle.h"
using namespace std;

int main(int argc, char* argv[])
{
	if( argc < 2) {
		cout << "./SudokuPuzzle (your input file)" << endl;
		exit(0);
	}

	string file1(argv[1]);
	SudokuPuzzle puzzle(file1);

	int check = puzzle.solve();

	if(check == 0)
	{
		cout << "Puzzle solved!\nSolved puzzle stored in solved.txt\n";
	}

	puzzle.output();
}
