/*
The Maze.
This is a game where you have to go through the maze and collect the items on the map.

1.Function Loop creates functions call, the generation of the world,
the game, the playing field, as the player will not pass all the levels;

2.LevelGenerator it retrieves an array of data from text files and
depending of type of the transferred loop variable level number. It translates from char to int;

3.WindowControl creates a map on the screen of the game,
turn handles and sends the value to the function Data(4);

4.Function Data implements the data collection made by the player in the map array
and the collected items and the number of lives,
the number of levels in which to create the conditions to continue or interrupt the game;

5.Function GameOver implements a window with text "Game Over", and out of the game, or offering to continue;

6.Function Victory implements a text box deducing victory and offering to continue;

7.Description elements of array:
0 - Path
1 - Wall
2 - Spawnpoint(fixed)
3 - Exit

Made by greendy5.
*/

#include <iostream>
#include <conio.h>
#include <fstream>
#ifdef _WIN32 || _WIN64
#include <windows.h>
#endif

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
void GameOver(unsigned short LevelNum, unsigned short Health){

	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t     Game Over!\n\n\n\n\n\n\n\n\n\n\n";

	if (Health < 1) { 
		_getch();
		exit(0); 
	}

	cout << "\t\t\t\t Do you want restart?[y]/[n]";
	cout << "\n\t\t\t\t\t";

	char choice;
	cin >> choice;
	switch (choice) {
	case 'y': {
		Health--;
		Loop(LevelNum, Health);
	} break;
	case 'n': exit(0); break;
	case 't': {
		unsigned short n;
		cout << "\t\t\t\t Input Level Number: ";
		cin >> n;
		LevelNum = n;
		Loop(LevelNum, Health);
	}
	default: GameOver(LevelNum, Health); break;
	}

}

void Victory(unsigned short LevelNum, unsigned short Health){

	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t     Victory!\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t Do you want continue?[y]/[n]";
	cout << "\n\t\t\t\t\t";

	char choice;
	cin >> choice;

	switch (choice) {
	case 'y': {
		LevelNum++;
		Loop(LevelNum, Health);
	} break;

	case 'n': exit(0); break;

	case 't': {
		unsigned short n;
		cout << "\t\t\t\t Input Level Number: ";
		cin >> n;
		LevelNum = n;
		Loop(LevelNum, Health);
	}
	default: Victory(LevelNum, Health); break;
	}

}

void Data(unsigned short Management, unsigned short StopGame, unsigned short Score, unsigned short Items, unsigned short LevelNum, unsigned short Health){
	if (Management == 1) 
	{
		GameOver(LevelNum, Health);
		StopGame = 1;
	}
	if (Management == 3)
	{
		if (Score == Items)
		{
			Victory(LevelNum, Health);
			StopGame = 1;
		}
		else
		{
			GameOver(LevelNum, Health);
			StopGame = 1;
		}
	}
	Management = 2;
}
void WindowControl(unsigned short LevelNum, unsigned short Items, char LevelArray[24][24], unsigned short Health, unsigned short y, unsigned short x) {

	unsigned short keysArrow;
	unsigned short heart = 3;
	unsigned short Score = 0;
	unsigned short StopGame(0);

	do {

		/*system("Cls");*/
		/*ClrScr();*/
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

		keysArrow = _getch();
		keysArrow = _getch();
		if (keysArrow == 0) keysArrow = _getch();
		switch (keysArrow) {
		case 80: {
			LevelArray[y][x] = 1;
			y++;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], StopGame, Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 72: {
			LevelArray[y][x] = 1;
			y--;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], StopGame, Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 77: {
			LevelArray[y][x] = 1;
			x++;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], StopGame, Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 75: {
			LevelArray[y][x] = 1;
			x--;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], StopGame, Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		/*case 107: {
			LevelArray[y][x] = 0;
			y++;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], StopGame, Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 105: {
			LevelArray[y][x] = 0;
			y--;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], StopGame, Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 108: {
			LevelArray[y][x] = 0;
			x++;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], StopGame, Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;
		case 106: {
			LevelArray[y][x] = 0;
			x--;
			if (LevelArray[y][x] == 4) {
				Score++;
			}
			Data(LevelArray[y][x], StopGame, Score, Items, LevelNum, Health);
			LevelArray[y][x] = 2;
		}break;*/

		default: WindowControl(LevelNum, Items, LevelArray, Health, y, x); break;
		}
	} while (true);
}
void LevelGenerator(unsigned short LevelNum, unsigned short Health) {

	char LevelArray[24][24];
	unsigned short Items = 0;
	unsigned short y = 0;
	unsigned short x = 0;
	ifstream InputLevel1("level1.txt");
	ifstream InputLevel3("level2.txt");
	ifstream InputLevel2("level3.txt");
	ifstream InputLevel4("level4.txt");
	ifstream InputLevel5("level5.txt");
	switch (LevelNum) {
	case 1:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {
				InputLevel1.get(LevelArray[i][j]);
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;
				if (LevelArray[i][j] == 2) {
					y = i;
					x = j;
				}
			}
		}
	} break;
	case 2:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {
				InputLevel2.get(LevelArray[i][j]);
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;
				if (LevelArray[i][j] == 2) {
					y = i;
					x = j;
				}
			}
		}
	} break;
	case 3:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {
				InputLevel3.get(LevelArray[i][j]);
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;
				if (LevelArray[i][j] == 2) {
					y = i;
					x = j;
				}
			}
		}
	} break;
	case 4:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {
				InputLevel4.get(LevelArray[i][j]);
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;
				if (LevelArray[i][j] == 2) {
					y = i;
					x = j;
				}
			}
		}
	} break;
	case 5:
	{
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; j++) {
				InputLevel5.get(LevelArray[i][j]);
				LevelArray[i][j] = LevelArray[i][j] - '0';
				if (LevelArray[i][j] == 4) Items++;
				if (LevelArray[i][j] == 2) {
					y = i;
					x = j;
				}
			}
		}
	} break;
	}

	WindowControl(LevelNum, Items, LevelArray, Health, y, x);
}
void Loop(unsigned short LevelNum, unsigned short Health) {
	while (LevelNum<6) {
		LevelGenerator(LevelNum, Health);
	} if (LevelNum == 6) {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\t Well done!";
		_getch();
		exit(0);
	}
}
void Menu() {

	unsigned short MenuNum;
	unsigned short Wall = 176;
	unsigned short Door = 177;

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
				unsigned short l = 178;
				cout << (char)l;
				cout << (char)l;
			}
		}
		cout << "\n\t\t\t";
	}
	cout << "\n\t\t\tGame menu:";
	cout << "\n\n\t\t\t 1. Play game";
	cout << "\n\t\t\t 2. Choose level";
	cout << "\n\t\t\t 3. Game rules";
	cout << "\n\t\t\t 4. Quit\n\t\t\t";

	cin >> MenuNum;
	switch (MenuNum) {
	case 1: {
		unsigned short LevelNum = 1;
		unsigned short Health = 3;
		Loop(LevelNum, Health);
	} break;
	case 2: {
		system("cls");
		unsigned short LevelNum;
		unsigned short Health = 3;
		cout << "\n\n\t\tChoose level (1-5)";
		cin >> LevelNum;
		Loop(LevelNum, Health);
	}break;
	case 3: {
		system("cls");
		cout << "\n\n\t\t GAME RULES \n \t\t 1) Player(You):  [] \n\t\t 2) Items(You must collect all of them to escape level):  <> \n\t\t 3) Walls(You shouldn`t take collision with it):  "
			<< (char)Wall << (char)Wall << "\n\t\t 4) Door(If You want to win, You should go there):  " << (char)Door << (char)Door << "\n\t\t 5) You have 3 lifes" << "\n\n\n\t\t Press some key to escape..." << endl;
		_getch();
		system("cls");
		Menu();
	}break;
	case 4: {
		exit(0);
	}break;
	default: Menu(); break;
	}


}

int main() {

	Menu();
	return 0;

}