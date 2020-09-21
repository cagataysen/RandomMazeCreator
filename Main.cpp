#include <iostream>
#include <ctime>
#include <windows.h> //to have sleep

using namespace std;
time_t t0;
const int mazeDimensions = 12;
int freeSpace = 0;
int Wall = 1;
bool foundExit = false;

void mazeTraverse(int m[mazeDimensions][mazeDimensions], int r, int c, int direction);
void makeMove(int m[mazeDimensions][mazeDimensions], int &r, int &c, int &direction);
int right(int m[mazeDimensions][mazeDimensions], int r, int c);
int left(int m[mazeDimensions][mazeDimensions], int r, int c);
int up(int m[mazeDimensions][mazeDimensions], int r, int c);
int down(int m[mazeDimensions][mazeDimensions], int r, int c);

void move(int m[mazeDimensions][mazeDimensions], int &r, int &c);
bool canMove(int m[mazeDimensions][mazeDimensions], int r, int c);
void motion(int m[mazeDimensions][mazeDimensions], int &r, int &c);
bool canmotion(int m[mazeDimensions][mazeDimensions], int r, int c);
void creatingMaze(int m[mazeDimensions][mazeDimensions], int r, int c);
int findStart();
void printScreen(int m[mazeDimensions][mazeDimensions]);
void change3to0(int m[mazeDimensions][mazeDimensions]);

int main()
{
	int highscore; 

	srand(time(0));

	int maze[mazeDimensions][mazeDimensions] = { 0 };

	for (int i = 0; i < mazeDimensions; ++i)
		for (int j = 0; j < mazeDimensions; ++j)
			maze[i][j] = 1;

	int r = findStart();
	//int r = 0;
	int c = 0;//changes the location of the car

	maze[r][c] = 0;

	creatingMaze(maze, r, c);
	change3to0(maze);
	maze[r][c] = 2;
	/*printScreen(maze);
	system("pause");*/
	t0 = time(0);
	mazeTraverse(maze, r, c, 3);
	foundExit = false;
	for (int i = 0; i < mazeDimensions; ++i)
		for (int j = 0; j < mazeDimensions; ++j)
			maze[i][j] = 1;
	maze[r][c] = 0;

	creatingMaze(maze, r, c);
	cout << "Press enter to pass abaubacar level 2" << endl;
	cin.get(); //it doesnt want any string so i added this
	change3to0(maze);
	maze[r][c] = 2;
	/*printScreen(maze);
	system("pause");*/
	mazeTraverse(maze, r, c, 3);
	cout << "highscore = " << 1200 - ((time(0) - t0) * 10) << endl; // t0 = initial time, time(0) = current time,  ( current - time = passed time)
	system("pause");
	return 0;
}

void creatingMaze(int m[mazeDimensions][mazeDimensions], int r, int c)
{

	bool made = false;

	while (made == false)
	{
		if (c == mazeDimensions - 1) //exit is going to be on 11. column
			foundExit = true;


		if (canmotion(m, r, c))
		{
			motion(m, r, c);
			//printScreen(m);
			//system("pause");
		}
		else if (canMove(m, r, c))
		{
			m[r][c] = 3; //3 means you can't action from that square
						 //printScreen(m);
						 //system("pause");
			move(m, r, c); //move to first open square that can be found
		}
		else
			made = true;

	}

	printScreen(m);
}






bool canMove(int m[mazeDimensions][mazeDimensions], int r, int c) 
{//true there spaces will be neighbor 
	if (m[r][c + 1] == 0)
		return true;
	else if (m[r + 1][c] == 0)
		return true;
	else if (m[r][c - 1] == 0)
		return true;
	else if (m[r - 1][c] == 0)
		return true;
	else
		return false;
}

void move(int m[mazeDimensions][mazeDimensions], int &r, int &c)//for motion
{//this is written for makemove directions
	if (m[r][c + 1] == 0)
		c++;
	else if (m[r + 1][c] == 0)
		r++;
	else if (m[r][c - 1] == 0)
		c--;
	else if (m[r - 1][c] == 0)
		r--;
	else
		cout << "We have a problem..." << endl;

}


void motion(int m[mazeDimensions][mazeDimensions], int &r, int &c) //find a way and move on
{
	bool foundPath = false;

	while (foundPath == false)
	{

		int direction = (1 + rand() % 4) * 3;//case 3,6,9,12 
											 //if there was only rand() % 4 it would start with case 0


		switch (direction)
		{
		case 3:
			if (c + 1 <= mazeDimensions - 1
				&& m[r][c + 2] == Wall
				&& m[r - 1][c + 1] == Wall && m[r + 1][c + 1] == Wall
				&& m[r][c + 1] == Wall)
			{
				if (c == mazeDimensions - 2 && foundExit == true)
					; //if you get to the exit do nothing
				else
				{
					c++;
					foundPath = true;
				}
			}
			break;
		case 6:
			if (r + 1 <= mazeDimensions - 2
				&& m[r + 2][c] == Wall
				&& m[r + 1][c + 1] == Wall && m[r + 1][c - 1] == Wall
				&& m[r + 1][c] == Wall
				&& c != 0 && c != mazeDimensions - 1)
			{
				r++;
				foundPath = true;
			}
			break;
		case 9:
			if (c - 1 >= 0
				&& m[r][c - 2] == Wall
				&& m[r - 1][c - 1] == Wall && m[r + 1][c - 1] == Wall
				&& m[r][c - 1] == Wall
				&& c - 1 != 0)
			{
				c--;
				foundPath = true;
			}
			break;
		case 12:
			if (r - 1 >= 1
				&& m[r - 2][c] == Wall
				&& m[r - 1][c + 1] == Wall && m[r - 1][c - 1] == Wall
				&& m[r - 1][c] == Wall
				&& c != 0 && c != mazeDimensions - 1)
			{
				r--;
				foundPath = true;
			}
			break;
		}
	}

	m[r][c] = 0; //move on

}



bool canmotion(int m[mazeDimensions][mazeDimensions], int r, int c) //eger bitisik kareler hareket ettirilebiliyorsa return true
{
	bool motionable = false;

	if (r <= mazeDimensions - 3
		&& m[r + 2][c] == Wall
		&& m[r + 1][c + 1] == Wall && m[r + 1][c - 1] == Wall
		&& m[r + 1][c] == Wall 
		&& c != 0 && c != mazeDimensions - 1)
	{
		motionable = true;
	}
	else if (c <= mazeDimensions - 2
		&& m[r][c + 2] == Wall
		&& m[r - 1][c + 1] == Wall && m[r + 1][c + 1] == Wall
		&& m[r][c + 1] == Wall)
	{
		if (c == mazeDimensions - 2 && foundExit == true)
			; //bi sey yapma
		else
		{
			motionable = true;
		}
	}
	else if (r >= 2
		&& m[r - 2][c] == Wall
		&& m[r - 1][c + 1] == Wall && m[r - 1][c - 1] == Wall
		&& m[r - 1][c] == Wall
		&& c != 0 && c != mazeDimensions - 1) //zora girmediysen saga ya da sola git 
	{
		motionable = true;
	}
	else if (c >= 1
		&& m[r][c - 2] == Wall
		&& m[r - 1][c - 1] == Wall && m[r + 1][c - 1] == Wall
		&& m[r][c - 1] == Wall
		&& c - 1 != 0)
	{
		motionable = true;
	}

	return motionable;
}

int findStart()
{
	return 1 + rand() % (mazeDimensions - 2); // arabanin baslayacagi yeri bulan matematiksel islem
}

void printScreen(int m[mazeDimensions][mazeDimensions]) //labirenti ekrana yazdiran kod
{

	cout << time(0) - t0 << endl;

	for (int i = 0; i < mazeDimensions; ++i) {
		for (int j = 0; j < mazeDimensions; ++j)
		{
			switch (m[i][j])
			{
			case 0:
				cout << "  ";
				break;
			case 1:
				cout << "# ";
				break;
			case 2:
				cout << "O ";
				break;
			case 3:
				cout << "  ";
				break;
			}
		}
		cout << endl;

	}
	Sleep(100);
}

void mazeTraverse(int m[mazeDimensions][mazeDimensions], int r, int c, int direction)
{//if you get the exit write congrats 
 //if you cant get to the exit keep moving

	if (c == mazeDimensions - 1)
	{
		cout << "\nCONGRATS!" << endl;

	}
	else
	{
		//resetMaze(m);
		int pr = r;
		int pc = c;

		makeMove(m, r, c, direction);
		m[r][c] = 2;  //the car at the case 2 so = O
		m[pr][pc] = 0;//
		printScreen(m);

		system("cls");
		mazeTraverse(m, r, c, direction);
										 
	}
}

void makeMove(int m[mazeDimensions][mazeDimensions], int &r, int &c, int &direction)
{
 /*
 3 - right
 6 - down
 9 - left
 12 - up
 */

	switch (direction) //önce fonksiyonları tanımlıyoruz switch case içinde
	{
	case 3:
		direction = right(m, r, c);
		break;
	case 6:
		direction = down(m, r, c);
		break;
	case 9:
		direction = left(m, r, c);
		break;
	case 12:
		direction = up(m, r, c);
		break;
	}

	switch (direction)
	{
	case 3://right
		c++;
		break;
	case 6://down
		r++;
		break;
	case 9://left
		c--;
		break;
	case 12://up
		r--;
		break;
	}
}

//try and move down
//if can't, try and move right
//if can't, try and move up
//if can't, try and move left
//if can't, declare that you are stuck



int right(int m[mazeDimensions][mazeDimensions], int r, int c)
{
	if (m[r + 1][c] == 0)
		return 6;  	
	else if (m[r][c + 1] == 0)
		return 3;  
	else if (m[r - 1][c] == 0)
		return 12; 
	else if (m[r][c - 1] == 0)
		return 9;
	else
		cout << "\nStuck!" << endl;

	return 0;
}

int left(int m[mazeDimensions][mazeDimensions], int r, int c)
{
	if (m[r - 1][c] == 0)
		return 12;
	else if (m[r][c - 1] == 0)
		return 9;
	else if (m[r + 1][c] == 0)
		return 6;
	else if (m[r][c + 1] == 0)
		return 3;
	else
		cout << "\nStuck!" << endl;

	return 0;
}

int up(int m[mazeDimensions][mazeDimensions], int r, int c)
{
	if (m[r][c + 1] == 0)
		return 3;
	else if (m[r - 1][c] == 0)
		return 12;
	else if (m[r][c - 1] == 0)
		return 9;
	else if (m[r + 1][c] == 0)
		return 6;
	else
		cout << "\nStuck!" << endl;

	return 0;
}


int down(int m[mazeDimensions][mazeDimensions], int r, int c)
{
	if (m[r][c - 1] == 0)
		return 9;
	else if (m[r + 1][c] == 0)
		return 6;
	else if (m[r][c + 1] == 0)
		return 3;
	else if (m[r - 1][c] == 0)
		return 12;
	else
		cout << "\nStuck!" << endl;

	return 0;
}
void change3to0(int m[mazeDimensions][mazeDimensions])
{
	for (int i = 0; i < mazeDimensions; ++i) {
		for (int j = 0; j < mazeDimensions; ++j) {
			if (m[i][j] == 3)
				m[i][j] = 0;
		}
	}

}
