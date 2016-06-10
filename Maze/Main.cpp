/*
The Maze.
This is a game where you have to go through the maze and collect all items on the map.

1.Function Loop creates functions call, the generation of the world,
the game, the playing field, as the player will not pass all the levels;

2.LevelGenerator it retrieves an array of data from text files and
depending of type of the transferred loop variable level number. It translates from char to int;

3.WindowControl creates a map on the screen of the game,
turn handles and sends the value to the function "Data";

4.Function Data implements the data collection made by the player in the map array
and the collected items and the number of lives,
the number of levels in which to create the conditions to continue or interrupt the game;

5.Function GameOver implements a window with text "Game Over", and out of the game, or offering to continue;

6.Function Victory implements a text box deducing victory and offering to continue;

7.Description elements of array:
0 - Path
1 - Wall
2 - Spawnpoint ("player")
3 - Exit
4 - Items ("food")

Made by greendy5.
*/
#include <time.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#ifdef _WIN32 || _WIN64
#include <windows.h>
#endif
// function, which erase screen, it can be used only in Windows OS
void ClrScr()
{
#ifdef _WIN32 || _WIN64
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	COORD coord = { 0, 0 };
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info))
		return;
	int spaceCount = buffer_info.dwSize.X * buffer_info.dwSize.Y;
	unsigned long spaceWriten;
	if (!FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', spaceCount, coord, &spaceWriten))
	{
		std::cerr << "Could not fill console width spaces";
		return;
	}
	if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord))
	{
		std::cerr << "Could not set cursor position";
		return;
	}
#else
#error This platform doesn't support
#endif
}

using namespace std;

void Loop(unsigned short LevelNum, unsigned short Health);
void Menu(unsigned short Arrow);

void GameOver(unsigned short LevelNum, unsigned short Health, unsigned short Arrow){
	
	ClrScr(); // it cleans screen (it's stable analog of system("cls")
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t     Game Over!\n\n\n\n\n\n";

	if (Health < 1) { // it stops game, if count of lives = 0
		_getch();
		Menu(1);
	}

	cout << "\t\t\t\t Do you want restart?[y]/[n]";							// it can continue game, if player lost previous play
	cout << (Arrow == 1 ? "\n\n\t\t\t\t ->" : "\n\n\t\t\t\t   ") << " Yes";
	cout << (Arrow == 2 ? "\n\n\t\t\t\t ->" : "\n\n\t\t\t\t   ") << " No";

	unsigned short Category = _getch();										// it realise "Arrow control" to continue or quit to main menu

	switch (Category) {
	case 72: {
		Arrow--;
		if (Arrow < 1) Arrow = 2;
		GameOver(LevelNum, Health, Arrow);
	} break;
	case 80: {
		Arrow++;
		if (Arrow > 2) Arrow = 1;
		GameOver(LevelNum, Health, Arrow);
	} break;
	case 13: {
		switch (Arrow) {
		case 1: {
			Health--;
			Loop(LevelNum, Health);
		}break;
		case 2: {
			Menu(1);
		}break;
		}
	} break;
	default: GameOver(LevelNum, Health, Arrow); break;						//prevents default keys to escape errors
	}
}

void Victory(unsigned short LevelNum, unsigned short Health, unsigned short Arrow){
	ClrScr();
	if (LevelNum == 5) {
		ClrScr();
		cout << "\n\n\n\n\n\n\t\t\t\t Well done!";
		_getch();
		exit(0);
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t     Victory!\n\n\n\n\n\n\n\t\t\t\t Do you want continue?[y]/[n]";
	cout << (Arrow == 1 ? "\n\n\t\t\t\t ->" : "\n\n\t\t\t\t   ") << " Yes";
	cout << (Arrow == 2 ? "\n\n\t\t\t\t ->" : "\n\n\t\t\t\t   ") << " No";

	unsigned short Category = _getch();										// "Arrow control"

	switch (Category) {
	case 72: {
		Arrow--;
		if (Arrow < 1) Arrow = 2;
		Victory(LevelNum, Health, Arrow);
	} break;
	case 80: {
		Arrow++;
		if (Arrow > 2) Arrow = 1;
		Victory(LevelNum, Health, Arrow);
	} break;
	case 13: {
		switch (Arrow) {
		case 1: {
			LevelNum++;
			Loop(LevelNum, Health);
		}break;
		case 2: {
			Menu(1);
		}break;
		}
	} break;
	default: Victory(LevelNum,Health, Arrow); break;
	}
}

void Data(unsigned short Management, unsigned short Score, unsigned short Items, unsigned short LevelNum, unsigned short Health){ // this function directs to function of "Win"(Victory) or "Lose"(GameOver) (Number == Number of Wall)
	unsigned short Arrow = 1;					
	if (Management == 1)								
	{
		GameOver(LevelNum, Health, Arrow);

	}
	if (Management == 3)								//(DoorNum)
	{
		if (Score == Items)								// If Player collects all items, he will win a level 
		{

			Victory(LevelNum, Health, Arrow);			
		}
		else
		{
			GameOver(LevelNum, Health, Arrow);		   
		}
	}
	Management = 2;									   //(PlayerNum)
}
void WindowControl(unsigned short LevelNum, unsigned short Items, char LevelArray[24][24], unsigned short Health, unsigned short y, unsigned short x) {

	unsigned short Key;
	unsigned short Score = 0;

	for (;;) {

		ClrScr();

		for (unsigned short i = 0; i < 23; i++)
		{
			for (unsigned short j = 0; j < 23; j++)
			{
				switch (LevelArray[i][j]) {
				case 0: {cout << "  "; }break;

				case 1: {
					unsigned short l = 176;
					cout << (char)l << (char)l;
				}break;

				case 2: {cout << "[]"; }break;

				case 3: {
					unsigned short l = 177;
					cout << (char)l << (char)l;
				}break;

				case 4: {cout << "<>"; }break;
				}
			}
			cout << endl;
		}

		cout << "Level: " << LevelNum << endl;
		cout << "Lifes: " << Health << endl;
		cout << "Collected <>: " << Score << "/" << Items << endl;

		Key = _getch();
		if (Key == 224) Key = _getch();
		
		switch (Key) {
		case 80: { //Up
			LevelArray[y][x] = 1;
			y++;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 72: { //Down
			LevelArray[y][x] = 1;
			y--;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 77: { //Right
			LevelArray[y][x] = 1;
			x++;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 75: { //Left
			LevelArray[y][x] = 1;
			x--;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;

		default: Data(LevelArray[y][x], Score, Items, LevelNum, Health); break;
		}
	} 
}
void LevelGenerator(unsigned short LevelNum, unsigned short Health) {

	char LevelArray[24][24];
	unsigned short Items = 0;
	unsigned short y = 0;
	unsigned short x = 0;

	ifstream Map1("level1.txt");
	ifstream Map2("level2.txt");
	ifstream Map3("level3.txt");
	ifstream Map4("level4.txt");
	ifstream Map5("level5.txt");

	switch (LevelNum) {
	case 1:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {
				Map1.get(LevelArray[i][j]);				//level 1
				LevelArray[i][j] = LevelArray[i][j] - '0';		//Translate char into integer
				if (LevelArray[i][j] == 4) Items++;				//Sum of "Items" in file
				else if (LevelArray[i][j] == 2) {
					y = i;										//Player's coordinates 
					x = j;
				}
			}
		}
	} break;
	case 2:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {						//level 2
				Map3.get(LevelArray[i][j]);
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;				//Sum of "Items" in file
				else if (LevelArray[i][j] == 2) {
					y = i;										//Player's coordinates 
					x = j;
				}
			}
		}
	} break;
	case 3:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {						//level 3
				Map2.get(LevelArray[i][j]);
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;				//Sum of "Items" in file
				else if (LevelArray[i][j] == 2) {
					y = i;										//Player's coordinates 
					x = j;
				}
			}
		}
	} break;
	case 4:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {
				Map4.get(LevelArray[i][j]);				//level 4
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;				//Sum of "Items" in file
				else if (LevelArray[i][j] == 2) {
					y = i;										//Player's coordinates 
					x = j;
				}
			}
		}
	} break;
	case 5:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {						//level 5
				Map5.get(LevelArray[i][j]);
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;				//Sum of "Items" in file
				else if (LevelArray[i][j] == 2) {
					y = i;										//Player's coordinates 
					x = j;
				}
			}
		}
	} break;
	}
	WindowControl(LevelNum, Items, LevelArray, Health, y, x);
}

void Loop(unsigned short LevelNum, unsigned short Health) {
	while (LevelNum<6) {										//Number of cycles 
		LevelGenerator(LevelNum, Health);						//Generate level
	}
}

void SubMenu(unsigned short Arrow) {
	ClrScr();
	unsigned short Category;
	cout << "\n\n\t\t\t Choose level: ";					// The second point of Menu (choosing a level)

	cout << (Arrow == 1 ? "\n\t\t\t ->" : "\n\t\t\t   ") << " Level 1";
	cout << (Arrow == 2 ? "\n\t\t\t ->" : "\n\t\t\t   ") << " Level 2";
	cout << (Arrow == 3 ? "\n\t\t\t ->" : "\n\t\t\t   ") << " Level 3";
	cout << (Arrow == 4 ? "\n\t\t\t ->" : "\n\t\t\t   ") << " Level 4";
	cout << (Arrow == 5 ? "\n\t\t\t ->" : "\n\t\t\t   ") << " Level 5";
	cout << (Arrow == 6 ? "\n\t\t\t ->" : "\n\t\t\t   ") << " Exit to main menu";

	Category = _getch();
	if (Category == 224) Category = _getch();

	switch (Category) {
	case 72: {
		Arrow--;
		if (Arrow < 1) Arrow = 6;
		SubMenu(Arrow);
	} break;
	case 80: {
		Arrow++;
		if (Arrow > 6) Arrow = 1;
		SubMenu(Arrow);
	} break;
	case 13: {
		switch (Arrow) {			//choosing a level
		case 6: {
			Arrow = 1;
			Menu(Arrow);
		}break;
		default: {
			unsigned short LevelNum = Arrow;
			unsigned short Health = 3;
			Loop(LevelNum, Health);
			break;
		}
		}
	}
	}
}

void Menu(unsigned short Arrow) { // Starting menu

	ClrScr();
	unsigned short Category;
	unsigned short l = 178;
	int IntroArray[5][23] = {
		{ 1,0,0,0,1,0,0,1,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1, },
		{ 1,1,0,1,1,0,1,0,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0, },
		{ 1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1,0, },
		{ 1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0, },
		{ 1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1, } };
	cout << "\n\t\t\t";
	for (unsigned short i = 0; i < 5; i++) {
		for (unsigned short j = 0; j < 23; j++) {
			if (IntroArray[i][j] == 0) {
				cout << "  ";
			} else {
				cout << (char)l;
				cout << (char)l;
			}
		}
		cout << "\n\t\t\t";
	}

	cout <<(Arrow == 1 ? "\n\t\t\t >>" : "\n\t\t\t   ") <<" Play";
	cout <<(Arrow == 2 ? "\n\t\t\t >>" : "\n\t\t\t   ") <<" Choose level";
	cout <<(Arrow == 3 ? "\n\t\t\t >>" : "\n\t\t\t   ") <<" Game rules";
	cout <<(Arrow == 4 ? "\n\t\t\t >>" : "\n\t\t\t   ") <<" Quit\n\t\t\t  ";

	Category = _getch();
	if (Category == 224) Category = _getch();
	
	switch (Category) {
	case 72: {
		Arrow--;
		if (Arrow < 1) Arrow = 4;
		Menu(Arrow);
	} break;
	case 80: {
		Arrow++;
		if (Arrow > 4) Arrow = 1;
		Menu(Arrow);
	} break;
	case 13: {
		switch (Arrow) {
		case 1: {			//start game
			unsigned short LevelNum = 1;
			unsigned short Health = 3;
			Loop(LevelNum, Health);
		} break;
		case 2: {			//choosing a level
			Arrow = 1;
			SubMenu(Arrow);
		}break;
		case 3: {			//game rules
			unsigned short Wall = 176;
			unsigned short Door = 177;
			ClrScr();
			cout << "\n\n\t\t GAME RULES \n\t\t 1) Player(You):  [] \n\t\t 2) Items(You must collect all of them to escape level):  <> \n\t\t 3) Walls(You shouldn`t take collision with it):  "
				<< (char)Wall << (char)Wall << "\n\t\t 4) Door(If You want to win, You should go there):  " << (char)Door << (char)Door << "\n\t\t 5) You have 3 lifes" << "\n\n\n\t\t Press some key to escape..." << endl;
			_getch();
			Menu(Arrow);
		}break;
		case 4: {			//quit
			exit(0);
		}break;
		}
	} break;
	default: Menu(Arrow); break;
	}

}

int main() {
	system("color 01");
	unsigned short Arrow = 1;
	Menu(Arrow);
	return 0;

}