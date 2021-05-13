#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <conio.h>
#include <cwchar>
#include <stdio.h>

bool gameIsOn, quit = false;
using namespace std;
CONSOLE_FONT_INFOEX cfi;
bool level1 = false, level2 = false, level3 = false;
bool gameRunning;
int height, width;
int snakeX, snakeY;
char snakeTailX[300], snakeTailY[300];
int snakeTailLength;
int pointX, pointY, numberOfPoints;
enum direction { UP, DOWN, RIGHT, LEFT, NOTHING};
direction snakeDirection;
int photo = 0;
std::fstream file1;
std::string photoDescription;
void Movement()
{
	//movement with keys
	if (_kbhit())
	{ 
		switch (_getch())
		{
		case 'w':
			if (snakeDirection != DOWN) {
				snakeDirection = UP;
				photo = 1;
				break;
			}else break;
		case 's':
			if (snakeDirection != UP) {
				snakeDirection = DOWN;
				photo = 2;
				break;
			}
			else break;
		case 'a':
			if (snakeDirection != RIGHT) {
				snakeDirection = LEFT;
				photo = 3;
				break;
			}
			else break;
		case 'd':
			if (snakeDirection != LEFT) { //this if statement provides that snake cannot go into 'itself' cannot change 180 degree direction
				snakeDirection = RIGHT;
				photo = 4;
				break;
			}
		case 'f':
			photo = 1;
			break;
		}
	}
}
void WriteToFile(std::string photoDescription)
{
	switch (photo) {
	case 0:
		break;
	case 1:
		photoDescription = "Snake is moving upwards.";
		break;
	case 2:
		photoDescription = "snake is moving downwards.";
		break;
	case 3:
		photoDescription = "Snake is moving to the left.";
		break;
	case 4:
		photoDescription = "Snake is moving to the right.";
		break;
	}
	if (snakeX == pointX && snakeY == pointY)
	{
		photoDescription = "Snake has picked up the point!";
	}
	for (int i = 0; i < snakeTailLength; i++)
	{
		if (snakeTailX[i] == snakeX && snakeTailY[i] == snakeY)
		{
			photoDescription = "Snake has bitten its own tail! Good Game, GG!";
		}
	}
	file1 << photoDescription << std::endl;
}
void GameRules()
{
	int tempSnakeTailX = snakeTailX[0];
	int tempSnakeTailY = snakeTailY[0];

	int tempX, tempY;
	snakeTailX[0] = snakeX;
	snakeTailY[0] = snakeY;

	for (int i = 1; i < snakeTailLength; i++)
	{
		tempX = snakeTailX[i];
		tempY = snakeTailY[i];
		snakeTailX[i] = tempSnakeTailX;
		snakeTailY[i] = tempSnakeTailY;
		tempSnakeTailX = tempX;
		tempSnakeTailY = tempY;

	}
	
	//picking the point gives the point
	if (snakeX == pointX && snakeY == pointY)
	{
		numberOfPoints += 5;
		snakeTailLength++;
		pointX = rand() % width;
		pointY = rand() % height;

	}
	//snake moves constantly, we only make him turn 

	switch (snakeDirection)
	{
	case UP:
		snakeY--;
		break;
	case DOWN:
		snakeY++;
		break;
	case RIGHT:
		snakeX++;
		break;
	case LEFT:
		snakeX--;
		break;
	}
		
	//snake comes out on the other side of the thing when meets the wall
	if (snakeX >= width) snakeX = 0;
	if (snakeX < 0) snakeX = width - 1;
	if (snakeY >= height) snakeY = 0;
	if (snakeY < 0) snakeY = height - 1;
}
void GameOver()
{
	//if you bite your own tail you lose like in every snake game; loop for the whole length of the tail
	for (int i = 0; i < snakeTailLength; i++)
	{
		if (snakeTailX[i] == snakeX && snakeTailY[i] == snakeY)
		{
			

			std::this_thread::sleep_for(std::chrono::seconds(1)); //pause the game for a while
			system("CLS");
			cfi.dwFontSize.X = 30;
			cfi.dwFontSize.Y = 30;
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
			std::cout << "______________________________________" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "     SNECCOS DON'T BITE THEIR TAILS   " << std::endl;
			std::cout << std::endl;
			std::cout << "      returning to level choice...    " << std::endl;
			std::cout << "______________________________________" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(3)); //pause the game for a while
			gameRunning = false;
		}
	}

	//win conditions for different levels
	if (level1)
	{
		if (numberOfPoints == 40) 
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //pause the game for a while
			system("CLS");
			cfi.dwFontSize.X = 30;
			cfi.dwFontSize.Y = 30;
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
			std::cout << "______________________________________" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "           LEVEL 1 COMPLETE           " << std::endl;
			std::cout << "        returning to level choice...  " << std::endl;
			std::cout << "______________________________________" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //pause the game for a while
			level1 = false;
			gameRunning = false;
		}
	}
	else if (level2)
	{
		if (numberOfPoints == 60)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1)); //pause the game for a while
			system("CLS");
			cfi.dwFontSize.X = 30;
			cfi.dwFontSize.Y = 30;
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
			std::cout << "______________________________________" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "           LEVEL 2 COMPLETE           " << std::endl;
			std::cout << "        returning to level choice...  " << std::endl;
			std::cout << "______________________________________" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2)); //pause the game for a while
			level2 = false;
			gameRunning = false;
		}
	}
	else if (level3)
	{
		if (numberOfPoints == 60)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1)); //pause the game for a while
			system("CLS");
			cfi.dwFontSize.X = 30;
			cfi.dwFontSize.Y = 30;
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
			std::cout << "______________________________________" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "           LEVEL 3 COMPLETE           " << std::endl;
			std::cout << "        returning to level choice...  " << std::endl;
			std::cout << "______________________________________" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1)); //pause the game for a while
			level3 = false;
			gameRunning = false;
		}
	}




}
void MainMenu()
{
	bool inMainMenu = true;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 25;
	cfi.dwFontSize.Y = 40;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	system("CLS");
	std::cout << "______________________________________" << std::endl;
	std::cout << "              Main Menu:              " << std::endl;
	std::cout << "  (Press a number + enter to choose)  " << std::endl;
	std::cout << "              1. Play                 " << std::endl;
	std::cout << "              2. Quit                 " << std::endl;
	std::cout << "______________________________________" << std::endl;
	for (int i = 0; i < 5; i++)std::cout << std::endl;
	
	int choice;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		gameIsOn = true;
		break;
	case 2:
		quit = true;
		break;
	}
}
void LevelChoice() {
	system("CLS");
		std::cout << "______________________________________" << std::endl;
		std::cout << "            Choose a level            " << std::endl;
		std::cout << "              1. Level 1              " << std::endl;
		std::cout << "              2. Level 2              " << std::endl;
		std::cout << "              3. Level 3				" << std::endl;
		std::cout << "              4.  QUIT                " << std::endl;
		std::cout << "______________________________________" << std::endl;
		int levelChoice;
		std::cin >> levelChoice;
		switch (levelChoice)
		{
		case 1:
			level1 = true;
			break;
		case 2:
			level2 = true;
			break;
		case 3:
			level3 = true;
			break;
		case 4:
			gameIsOn = false;
			gameRunning = false;
			break;
		}
}
void Level1() 
{
	height = 15;
	width = 15;

	gameRunning = true;

	//position the snecco in the middle 
	snakeX = width - width / 3;
	snakeY = height - height / 3;
	pointX = rand() % width;
	pointY = rand() % height;
	numberOfPoints = 0;
	snakeDirection = NOTHING;
	snakeTailLength = 0;

}
void Level2()
{

	height = 17;
	width = 12;
	gameRunning = true;
	//position the snecco in the middle 
	snakeX = width - width / 3;
	snakeY = height - height / 3;
	pointX = rand() % width;
	pointY = rand() % height;
	numberOfPoints = 0;
	snakeDirection = NOTHING;
	snakeTailLength = 0;

}
void Level3()
{
	height = 10;
	width = 30;

	gameRunning = true;
	//position the snecco in the middle 
	snakeX = width - width / 3;
	snakeY = height - height / 3;
	pointX = rand() % width;
	pointY = rand() % height;
	numberOfPoints = 0;
	snakeDirection = NOTHING;
	snakeTailLength = 0;

}
void TerminalGraphics() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//first we want to clear the screen
	system("CLS");
	//create the area of the game
	for (int i = 0; i < width + 4; i++) //upper line
	{
		std::cout << "=";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0) std::cout << "||";

			//head of the snecco

			if (i == snakeY && j == snakeX)
			{


				std::cout << "0";
			}
			//points to collect
			else if (i == pointY && j == pointX) std::cout << "$";
			else
			{
				bool tailPrinted = false;//keeping track whether the tail was printed, this way it will not break the map, the blank spaces will be able to print correctly
				for (int z = 0; z < snakeTailLength; z++)
				{
					//printing the tail of the snake
					if (snakeTailX[z] == j && snakeTailY[z] == i)
					{
						std::cout << "s";
						tailPrinted = true;
					}
				}
				if (!tailPrinted) std::cout << " ";
			}
			if (j == width - 1) std::cout << "||";
		}
		std::cout << std::endl;
	}


	for (int i = 0; i < width + 4; i++) //lower line + 4 so it looks nicer

	{
		std::cout << "=";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Number Of Points: " << numberOfPoints << std::endl;

}


int main()
{
	file1.open("results.txt", std::ios::out);
	if (!file1.good())
	{
		std::cout << "Error" << std::endl;
		return 1;
	}

	while (!quit)
	{

		MainMenu();
		while (gameIsOn)
		{
			LevelChoice();

			cfi.dwFontSize.X = 0;
			cfi.dwFontSize.Y = 25;
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

			if (level1) Level1();
			else if (level2) Level2();
			else if (level3) Level3();


			while (gameRunning)
			{
				GameRules();
				TerminalGraphics();
				Movement();
				WriteToFile(photoDescription);
				GameOver();
				photo = 0;
			}
		}
		
	}
	file1.close();
	return 0;
}
	

