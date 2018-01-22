#include <iostream>
#include "./SudokuPuzzle.h"
#include <sys/time.h>
using namespace std;

typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

int main(int argc, char* argv[])
{
	if( argc < 2) {
		cout << "./SudokuPuzzle (your input file)" << endl;
		exit(0);
	}

	string file1(argv[1]);
	SudokuPuzzle puzzle(file1);

	timestamp_t t0 = get_timestamp();
	int check = puzzle.solve();
	timestamp_t t1 = get_timestamp();
	double secs = (t1 - t0) / 1000000.0L;

	if(check == 0)
	{
		cout << "Puzzle solved in " << secs << " seconds!\nSolved puzzle stored in solved.txt\n";
	}

	puzzle.output();
}
