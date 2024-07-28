#include<iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include<fstream>
#include<algorithm>

using namespace std;

const int height = 50;
const int width = 32;
int lives = 3;
bool flag = true;
bool jump = true;

int ramboLocation[2] = { 46,18 };
int TankLocation[3][2] = { 0 };
int obstacleLocation[3][2] = { 0 };
int bulletLocation[3][2];

int distanceCovered = 0;
int highscore = 0;

void movement(char grid[height][width]);
void obstacles(char grid[height][width]);
void tanksummon(char grid[height][width]);
void stepdown(char grid[height][width]);
void printGrid(char grid[height][width]);
void ramboPrint(char grid[height][width]);
void readHighScores(int topScores[]);
void writeHighScores(int topScores[]);
void displayTopScores(int topScores[]);
void bulletUp(char grid[height][width]);
void displayMessage();
void points();

int main()
{
	ramboLocation[1] = 18;
	int choice;
	char name[50];

	cout << "---------------------------------" << endl;
	cout << "|WELCOME!TO JOHN RAMBO CONSOLE GAME|" << endl;
	cout << "-----------------------------------" << endl;
	cout << "Enter 1 to play" << endl;
	cout << "Enter 2 for instructions" << endl;
	cout << "Enter 3 to quit" << endl;
	cin >> choice;
	if (choice == 1) {
		cout << "Enter your name:" << endl;
		cin >> name;

	}
	else if (choice == 2)
	{
		cout << "1.Move left and right by using left and right arrow keys respectively" << endl;
		cout << "2.Rambo can jump using space key. Jump when you see an obstacle" << endl;
		cout << "3.You can press K to shoot, to prevent yourself from collision!" << endl;
		cout << "4.Avoid obstacles,crates and tanks at all costs else you lose!" << endl;
		cout << "5.You can press space bar to jump over the obstacles!" << endl;
		cout << "6.Speed is double in the center 2 lanes!" << endl;
		_getch();

	}
	else if (choice == 3) 
	{
		exit(0);
	}
	char grid[height][width];
	srand(time(0));

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
			{
				grid[i][j] = '$';
			}
			else
			{
				grid[i][j] = ' ';
			}
		}
	}
	//rambo printing
	grid[46][17] = '{';
	grid[46][19] = '}';
	grid[46][16] = '~';
	grid[46][20] = '¬';
	grid[45][18] = '0';
	grid[46][18] = '*';

	int topScores[10];
	readHighScores(topScores);

	while (highscore != 5000)
	{
		obstacles(grid);
		tanksummon(grid);
		stepdown(grid);
		movement(grid);
		bulletUp(grid);
		points();
		printGrid(grid);
		ramboPrint(grid);
		if (lives < 0)
			break;
		Sleep(1);
	}

	cout << "Game Over!" << endl;
	cout << "Your highscore: " << highscore << endl;

	for (int i = 0; i < 10; ++i)
	{
		if (highscore > topScores[i])
		{
			// Insert the new high score
			for (int j = 9; j > i; --j)
			{
				topScores[j] = topScores[j - 1];
			}
			topScores[i] = highscore;
			break;
		}
	}

	// Sort the top scores in descending order
	sort(begin(topScores), end(topScores), greater<int>());
	displayTopScores(topScores);
	writeHighScores(topScores);
	system("pause");
	return 0;
}

void delay(int milliseconds)
{
	Sleep(milliseconds);
}

void points()
{
	distanceCovered += 1;
	if (distanceCovered % 2 == 0)
		highscore += 1;

	cout << endl << "Score : " << highscore;
	cout << endl << "Distance : " << distanceCovered << endl;
	cout << "lives \t";
	if (lives == 3)
		cout << "* * *\n";
	else if (lives == 2)
		cout << "* *\n";
	else
		cout << "* \n";
}

void movement(char grid[height][width])
{
	int rowofR;
	int colomnofR;

	if (ramboLocation[1] == 18 || ramboLocation[1] == 13) 
		system("color E5"); 
	else 
		system("color 9E"); 

	// Update high score
	if (highscore > 0 && highscore > distanceCovered)
	{
		highscore = distanceCovered;
	}
	//delay for road
	if (ramboLocation[1] == 18 || ramboLocation[1] == 13)
		delay(1);
	else
		delay(100);
	

	//rambo movement
	if (_kbhit())
	{
		flag = true;
		jump = true;
		int key = _getch();
		if (key == 65 || key == 97)
		{
			if (ramboLocation[1] > 3)
			{
				ramboLocation[1] -= 5;
			}
		}
		if (key == 100 || key == 68)
		{
			if (ramboLocation[1] < 28)
			{
				ramboLocation[1] += 5;
			}
		}
		if (key == 75 || key == 107)
		{
			grid[ramboLocation[0] + 1][ramboLocation[1]] = '!';
			flag = false;
		}
		if (key == 32)
		{
			jump = false;
		}

	}

	// Check for collision with obstacles
	for (int i = 0; i < 3; ++i)
	{
		if (ramboLocation[0] + 1 == obstacleLocation[i][0] && ramboLocation[1] == obstacleLocation[i][1])
		{
			if (flag && jump)
			{
				cout << "Collision with obstacle! You lost live!" << endl;
				cout << "Your Score: " << highscore << endl;
				lives--;

				_getch();
			}
		}
	}

	// Check for collision with tanks
	for (int i = 0; i < 3; ++i)
	{
		if (ramboLocation[0] == TankLocation[i][0] && ramboLocation[1] == TankLocation[i][1])
		{
			if (flag )
			{
				cout << "Collision with Tank! You lost live!" << endl;
				cout << "Your Score: " << highscore << endl;
				lives--;

				_getch();
			}
		}
	}
	//cout << endl << ramboLocation[0] << " " << ramboLocation[1];

	//cout << endl << "Tank 1 location :" << TankLocation[0][0] << " " << TankLocation[0][1];
	//cout << endl << "Tank 2 location :" << TankLocation[1][0] << " " << TankLocation[1][1];
	//cout << endl << "Tank 3 location :" << TankLocation[2][0] << " " << TankLocation[2][1];

	//cout << endl << "Obstacle 1 location :" << obstacleLocation[0][0] << " " << obstacleLocation[0][1];
	//cout << endl << "Obstacle 2 location :" << obstacleLocation[1][0] << " " << obstacleLocation[1][1];
	//cout << endl << "Obstacle 3 location :" << obstacleLocation[2][0] << " " << obstacleLocation[2][1];


	system("cls");
}


void readHighScores(int topScores[])
{
	ifstream inputFile("highscores.txt");

	if (inputFile.is_open())
	{
		for (int i = 0; i < 10; ++i)
		{
			inputFile >> topScores[i];
		}

		inputFile.close();
	}
}
void writeHighScores(int topScores[])
{
	ofstream outputFile("highscores.txt");

	if (outputFile.is_open())
	{
		for (int i = 0; i < 10; ++i)
		{
			outputFile << topScores[i] << endl;
		}

		outputFile.close();
	}
}
void displayTopScores(int topScores[])
{
	cout << "Top Ten High Scores:" << endl;

	for (int i = 0; i < 10; ++i)
	{
		cout << i + 1 << ". " << topScores[i] << endl;
	}
}

void obstacles(char grid[height][width])
{
	int numobstacle = 0;

	for (int i = 0; i < 3; i++)
	{
		if (obstacleLocation[i][1] == 0)
			numobstacle++;
		if (obstacleLocation[i][0] == 48)
		{
			obstacleLocation[i][1] = 0;
			obstacleLocation[i][0] = 4;
		}

	}
	for (int j = 0; j < numobstacle; j++)
	{
		int obstacleRow, obstacleCol, i;

		if (obstacleLocation[0][1] == 0)
			i = 0;
		else if (obstacleLocation[1][1] == 0)
			i = 1;
		else if (obstacleLocation[2][1] == 0)
			i = 2;

		do {
			obstacleRow = rand() % (height - 25) + 7;
			obstacleCol = rand() % 6 + 1;
		} while (grid[obstacleRow][obstacleCol] != ' ');

		obstacleLocation[i][0] = obstacleRow;
		switch (obstacleCol)
		{
		case 1:
			obstacleCol = 3;
			obstacleLocation[i][1] = 3;
			break;
		case 2:
			obstacleCol = 8;
			obstacleLocation[i][1] = 8;
			break;
		case 3:
			obstacleCol = 13;
			obstacleLocation[i][1] = 13;
			break;
		case 4:
			obstacleCol = 18;
			obstacleLocation[i][1] = 18;
			break;
		case 5:
			obstacleCol = 23;
			obstacleLocation[i][1] = 23;
			break;
		case 6:
			obstacleCol = 28;
			obstacleLocation[i][1] = 28;
			break;
		}

		grid[obstacleRow][obstacleCol] = '^';
		grid[obstacleRow][obstacleCol - 1] = '-';
		grid[obstacleRow][obstacleCol - 2] = '-';
		grid[obstacleRow][obstacleCol + 1] = '-';
		grid[obstacleRow][obstacleCol + 2] = '-';
	}
}

void tanksummon(char grid[height][width])
{
	int numTanks = 0;

	for (int i = 0; i < 3; i++)
	{
		if (TankLocation[i][1] == 0)
			numTanks++;
		if (TankLocation[i][0] == 48)
		{
			TankLocation[i][1] = 0;
			TankLocation[i][0] = 4;
		}
	}

	for (int j = 0; j < numTanks; j++)
	{
		int tankRow, tankCol, i;
		do
		{
			tankRow = rand() % (height - 20) + 10;
			tankCol = rand() % 6 + 1;
		} while (grid[tankRow][tankCol] != ' ');

		if (TankLocation[0][1] == 0)
			i = 0;
		else if (TankLocation[1][1] == 0)
			i = 1;
		else if (TankLocation[2][1] == 0)
			i = 2;

		TankLocation[i][0] = tankRow;
		TankLocation[i][1] = tankCol;

		switch (tankCol)
		{
		case 1:
			tankCol = 3;
			TankLocation[i][1] = 3;
			break;
		case 2:
			tankCol = 8;
			TankLocation[i][1] = 8;
			break;
		case 3:
			tankCol = 13;
			TankLocation[i][1] = 13;
			break;
		case 4:
			tankCol = 18;
			TankLocation[i][1] = 18;
			break;
		case 5:
			tankCol = 23;
			TankLocation[i][1] = 23;
			break;
		case 6:
			tankCol = 28;
			TankLocation[i][1] = 28;
			break;
		}

		grid[tankRow][tankCol] = '?';
		grid[tankRow - 3][tankCol - 1] = '\\';
		grid[tankRow - 3][tankCol] = '_';
		grid[tankRow - 3][tankCol + 1] = '/';
		grid[tankRow - 1][tankCol] = '.';
		grid[tankRow - 2][tankCol - 1] = 'o';
		grid[tankRow - 2][tankCol - 2] = '(';
		grid[tankRow - 2][tankCol + 1] = 'o';
		grid[tankRow - 2][tankCol + 2] = ')';
		grid[tankRow - 2][tankCol] = '.';
		grid[tankRow - 1][tankCol - 1] = '\\';
		grid[tankRow - 1][tankCol + 1] = '/';
	}
}


void stepdown(char grid[height][width])
{
	int length = 5;
	for (int i = height - 3; i >= 1; i--)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (grid[i + 1][j] == '!')
			{
				grid[i][j] = grid[i + 1][j];
				grid[i + 1][j] = ' ';
			}
			else if (grid[i][j] == '0' ) 
			{
				grid[i][j] = grid[i][j];
				// Update tank positions
					TankLocation[0][0] = i;
			}
			else
			{
				grid[i + 1][j] = grid[i][j];
			}
		}
	}

	// Update obstacle positions
	obstacleLocation[0][0]++;
	obstacleLocation[1][0]++;
	obstacleLocation[2][0]++;

	// Update tank positions
	TankLocation[0][0]++;
	TankLocation[1][0]++;
	TankLocation[2][0]++;
}

void ramboPrint(char grid[height][width])
{
	grid[ramboLocation[0]][ramboLocation[1]] = '0';
	grid[ramboLocation[0] + 1][ramboLocation[1] + 1] = '}';
	grid[ramboLocation[0] + 1][ramboLocation[1] - 1] = '{';
	grid[ramboLocation[0] + 1][ramboLocation[1]] = '8';

	grid[ramboLocation[0] + 1][ramboLocation[1] + 2] = '¬';
	grid[ramboLocation[0] + 1][ramboLocation[1] - 2] = '~';
}

void bulletUp(char grid[height][width])
{
	for (int i = 0; i < 3; ++i) 
	{
		if (bulletLocation[i][1] != 0) 
		{
			int bulletRow = bulletLocation[i][0];
			int bulletCol = bulletLocation[i][1];

			grid[bulletRow][bulletCol] = ' '; 

			bulletRow--; 

			if (bulletRow >= 0)
			{
				grid[bulletRow][bulletCol] = '!';
				bulletLocation[i][0] = bulletRow; 
			}
			else
			{
				bulletLocation[i][1] = 0; 
			}
		}
	}
}

void printGrid(char grid[height][width])
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			cout << grid[i][j];
		}
		cout << endl;
	}
}