#include <iostream>
#include "mazegen.h"

int main()
{
	Maze test;
	test.genMaze();
	cout << test << endl;
	test.solveMaze();
	cout << test << endl;
}
