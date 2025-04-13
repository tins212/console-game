#include <iostream>
#include "Game.h"
#include "Map.h"
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

// solves the issue of the travelling cursor
void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {

	Game game;
	hideCursor();

	cout << "Instructions: " << endl;
	cout << "W,A,S,D = movement " << endl;
	cout << "I = stats" << endl;
	cout << "T = travel " << endl << endl;
	cout << "Press enter to start";

	int start = _getch();

	system("cls");

	while (!game.is_game_over()) {

		game.display_stats();
		game.display();
	
		cout << "";
		char op = _getch();
		game.move(op);

		system("cls");
	}
	
	return 0;
}