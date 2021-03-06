#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class SudokuPuzzle
{
  private:
	int grid[9][9][10];
	bool zoneCheck(int v, int cr, int cc) //value, current row, current column
	{
		int zr, zc; //zone row, zone column
		if (cr >= 0 && cr <= 2)
		//determines what zone the value "v" is in. zr and zc are the coordinates of the starting element of the zone
		{
			zr = 0; //top row
			if (cc >= 0 && cc <= 2)
			{
				zc = 0;
			}
			else if (cc >= 3 && cc <= 5)
			{
				zc = 3;
			}
			else if (cc >= 6 && cc <= 8)
			{
				zc = 6;
			}
		}
		else if (cr >= 3 && cr <= 5)
		{
			zr = 3; //middle row
			if (cc >= 0 && cc <= 2)
			{
				zc = 0;
			}
			else if (cc >= 3 && cc <= 5)
			{
				zc = 3;
			}
			else if (cc >= 6 && cc <= 8)
			{
				zc = 6;
			}
		}
		else if (cr >= 6 && cr <= 8)
		{
			zr = 6; //bottom row
			if (cc >= 0 && cc <= 2)
			{
				zc = 0;
			}
			else if (cc >= 3 && cc <= 5)
			{
				zc = 3;
			}
			else if (cc >= 6 && cc <= 8)
			{
				zc = 6;
			}
		}
		for (int r = zr; r < (zr + 3); r++) //only searches the 3x3 zone. returns false if the zone already contains the value "v"
		{
			for (int c = zc; c < (zc + 3); c++)
			{
				if (grid[r][c][0] == v)
				{
					//cout << v << " failed at " << cr << " " << cc << endl;
					return false;
				}
			}
		}
		return true;
	}
	void zoneSet(int v, int cr, int cc)
	{
		int zr, zc;
		if (cr >= 0 && cr <= 2)
		//determines what zone the value "v" is in. zr and zc are the coordinates of the starting element of the zone
		{
			zr = 0;
			if (cc >= 0 && cc <= 2)
			{
				zc = 0;
			}
			else if (cc >= 3 && cc <= 5)
			{
				zc = 3;
			}
			else if (cc >= 6 && cc <= 8)
			{
				zc = 6;
			}
		}
		else if (cr >= 3 && cr <= 5)
		{
			zr = 3;
			if (cc >= 0 && cc <= 2)
			{
				zc = 0;
			}
			else if (cc >= 3 && cc <= 5)
			{
				zc = 3;
			}
			else if (cc >= 6 && cc <= 8)
			{
				zc = 6;
			}
		}
		else if (cr >= 6 && cr <= 8)
		{
			zr = 6;
			if (cc >= 0 && cc <= 2)
			{
				zc = 0;
			}
			else if (cc >= 3 && cc <= 5)
			{
				zc = 3;
			}
			else if (cc >= 6 && cc <= 8)
			{
				zc = 6;
			}
		}
		for (int r = zr; r < (zr + 3); r++)
		{
			for (int c = zc; c < (zc + 3); c++)
			{
				if (grid[r][c][v] == v) //if the possible value is available then set it to 0
				{
					grid[r][c][v] = 0;
				}
			}
		}
	}
	bool rowCheck(int v, int cr)
	{
		for (int c = 0; c < 9; c++) //searches the given row. returns false if the row already contains the value "v"
		{
			if (grid[cr][c][0] == v)
			{
				//cout << v << " failed in row " << cr << endl;
				return false;
			}
		}
		return true;
	}
	void rowSet(int v, int cr)
	{
		for (int c = 0; c < 9; c++)
		{
			if (grid[cr][c][v] == v) //if the possible value is available then set it to 0
			{
				grid[cr][c][v] = 0;
			}
		}
	}
	bool colCheck(int v, int cc)
	{
		for (int r = 0; r < 9; r++) //searches the given column. returns false if the column already contains the value "v"
		{
			if (grid[r][cc][0] == v)
			{
				//cout << v << " failed in col " << cc << endl;
				return false;
			}
		}
		return true;
	}
	void colSet(int v, int cc)
	{
		for (int r = 0; r < 9; r++)
		{
			if (grid[r][cc][v] == v) //if the possible value is available then set it to 0
			{
				grid[r][cc][v] = 0;
			}
		}
	}
	bool cellCheck(int v, int r, int c) //checks a single cell for the 3 cases: row, column, and zone
	{
		if (zoneCheck(v, r, c) && rowCheck(v, r) && colCheck(v, c))
			return true;
		else
			return false;
	}
	void setPossible()
	{
		int v;
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if (grid[r][c][0] != 0) //runs through the whole grid and sets the possible values for each cell
				{
					v = grid[r][c][0];
					colSet(v, c);
					rowSet(v, r);
					zoneSet(v, r, c);
				}
			}
		}
	}
	void setCellLoop()
	{
		int count = 0; //counts possible
		int sd;		   //singles possibility var.
		bool changed = true;
		int tmp[9]; //array of possible values for the cells in a zone/row/column
		int zr, zc; //zone row, zone column
		while (changed)
		{
			changed = false;
			for (int r = 0; r < 9; r++)
			{
				for (int c = 0; c < 9; c++)
				{
					setPossible();
					if (grid[r][c][0] == 0)
					{
						//set singles
						for (int d = 1; d < 10; d++)
						{
							if (grid[r][c][d] != 0) //if a number is found in the empty cell (cell of value 0), then search through the possibilities and count for every possiblility. also store the coord. of the current possibility found
							{
								count++;
								sd = d;
							}
						}
						if (count == 1) //if only one possibility found, use the stored coord. to change the cell value to the possibility
						{
							grid[r][c][0] = sd;
							//cout << "single: " << sd << " at " << r << " " << c << endl;
							changed = true;
							goto eocl;
						}
						else if (count == 0)
						{
							//cout << "notCorrect " << r << " " << c << endl;
							goto notCorrect;
						}
						count = 0;

						//for unique
						for (int i = 0; i < 9; i++)
						{
							tmp[i] = 0;
						}
						//for zone
						if (r >= 0 && r <= 2) //determines what zone the cell is in. zr and zc are the coordinates of the starting element of the zone
						{
							zr = 0; //top row
							if (c >= 0 && c <= 2)
							{
								zc = 0;
							}
							else if (c >= 3 && c <= 5)
							{
								zc = 3;
							}
							else if (c >= 6 && c <= 8)
							{
								zc = 6;
							}
						}
						else if (r >= 3 && r <= 5)
						{
							zr = 3; //middle row
							if (c >= 0 && c <= 2)
							{
								zc = 0;
							}
							else if (c >= 3 && c <= 5)
							{
								zc = 3;
							}
							else if (c >= 6 && c <= 8)
							{
								zc = 6;
							}
						}
						else if (r >= 6 && r <= 8)
						{
							zr = 6; //bottom row
							if (c >= 0 && c <= 2)
							{
								zc = 0;
							}
							else if (c >= 3 && c <= 5)
							{
								zc = 3;
							}
							else if (c >= 6 && c <= 8)
							{
								zc = 6;
							}
						}
						for (int cr = zr; cr < (zr + 3); cr++)
						{
							for (int cc = zc; cc < (zc + 3); cc++)
							{
								if (cr == r && cc != c && grid[cr][cc][0] == 0)
								{
									for (int cd = 1; cd < 10; cd++)
									{
										if (grid[cr][cc][cd] != 0)
										{
											tmp[grid[cr][cc][cd] - 1] = grid[cr][cc][cd]; //stores value of possibility into index of tmp. this prevents multiple of same value
										}
									}
								}
								else if (cr != r && grid[cr][cc][0] == 0)
								{
									for (int cd = 1; cd < 10; cd++)
									{
										if (grid[cr][cc][cd] != 0)
										{
											tmp[grid[cr][cc][cd] - 1] = grid[cr][cc][cd]; //stores value of possibility into index of tmp. this prevents multiple of same value
										}
									}
								}
							}
						}
						for (int d = 1; d < 10; d++)
						{
							if (grid[r][c][d] != 0 && grid[r][c][d] != tmp[grid[r][c][d] - 1]) //if a possible value of the cell is unique to the zone, then set the cell to that value
							{
								grid[r][c][0] = grid[r][c][d];
								//cout << "zone unique: " << grid[r][c][d] << " at " << r << " " << c << endl;
								changed = true;
								goto eocl;
							}
						}
						for (int i = 0; i < 9; i++)
						{
							tmp[i] = 0;
						}
						//for row
						for (int cc = 0; cc < 9; cc++)
						{
							if (cc != c && grid[r][cc][0] == 0)
							{
								for (int cd = 1; cd < 10; cd++)
								{
									if (grid[r][cc][cd] != 0)
									{
										tmp[grid[r][cc][cd] - 1] = grid[r][cc][cd];
									}
								}
							}
						}
						for (int d = 1; d < 10; d++)
						{
							if (grid[r][c][d] != 0 && grid[r][c][d] != tmp[grid[r][c][d] - 1]) //if a possible value of the cell is unique to the row, then set the cell to that value
							{
								grid[r][c][0] = grid[r][c][d];
								//cout << "row unique: " << grid[r][c][d] << " at " << r << " " << c << endl;
								changed = true;
								goto eocl;
							}
						}
						for (int i = 0; i < 9; i++)
						{
							tmp[i] = 0;
						}
						//for col
						for (int cr = 0; cr < 9; cr++)
						{
							if (cr != r && grid[cr][c][0] == 0)
							{
								for (int cd = 1; cd < 10; cd++)
								{
									if (grid[cr][c][cd] != 0)
									{
										tmp[grid[cr][c][cd] - 1] = grid[cr][c][cd];
									}
								}
							}
						}
						for (int d = 1; d < 10; d++)
						{
							if (grid[r][c][d] != 0 && grid[r][c][d] != tmp[grid[r][c][d] - 1]) //if a possible value of the cell is unique to the column, then set the cell to that value
							{
								grid[r][c][0] = grid[r][c][d];
								//cout << "column unique: " << grid[r][c][d] << " at " << r << " " << c << endl;
								changed = true;
								goto eocl;
							}
						}
					eocl:;
					}
				}
			}
		}
	notCorrect:;
	}
	bool isSolved()
	{
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if (grid[r][c][0] == 0)
				{
					return false;
				}
			}
		}
		return true;
	}
	bool isCorrect()
	{
		int count = 0;
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if (grid[r][c][0] == 0)
				{
					for (int d = 1; d < 10; d++)
					{
						if (grid[r][c][d] == 0)
						{
							count++;
						}
					}
					if (count == 9)
					{
						return false;
					}
					else
					{
						count = 0;
					}
				}
			}
		}
		return true;
	}
	void findLeastPoss(int &x, int &y, int &n)
	{
		int count = 0;
		n = 9;
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if (grid[r][c][0] == 0)
				{
					for (int d = 1; d < 10; d++)
					{
						if (grid[r][c][d] != 0)
						{
							count++; //counts the number possible
						}
					}
					if (count < n)
					{
						n = count; //if the number possible is less than the global possible save it and the coord.
						x = r;
						y = c;
					}
					else
					{
						count = 0;
					}
				}
			}
		}
	}

  public:
	SudokuPuzzle(string f) //reads in the sudoku puzzle and sets possible
	{
		ifstream infs(f.c_str());
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				infs >> grid[r][c][0];
				for (int d = 1; d < 10; d++)
				{
					if (grid[r][c][0] != 0)
					{
						grid[r][c][d] = 0; //sets all possible for that cell to 0 if a value was given
					}
					else
					{
						grid[r][c][d] = d; //fills possible if no value was given
					}
				}
			}
		}
		infs.close();
	}
	int solve()
	{
		int rValue;
		if (isCorrect() && !isSolved())
		{
			setCellLoop();
		}
		if (!isCorrect())
		{
			return 1;
		}
		if (isSolved())
		{
			return 0;
		}
		int x = 0, y = 0, n; //x and y are the coord. and n is the number possible
		findLeastPoss(x, y, n);
		//cout << x << " " << y << " " << n << endl;
		for (int d = 1; d < 10; d++)
		{
			if (grid[x][y][d] != 0)
			{
				grid[x][y][0] = grid[x][y][d]; //recursively goes through and checks each possibility. if the puzzle becomes solved it bails out. if not it check the next possibility
				rValue = solve();
				if (rValue == 0)
				{
					return 0;
				}
			}
		}
	}
	void output(bool pretty = false)
	{
		ofstream ofs;
		ofs.open("solved.txt");
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				ofs << grid[r][c][0] << " ";
				if (pretty && (c + 1) % 3 == 0)
				{
					ofs << "| ";
				}
			}
			ofs << endl;
			if (pretty && (r + 1) % 3 == 0)
			{
				ofs << "----------------------\n";
			}
		}
		ofs.close();
	}
};
