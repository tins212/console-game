#include <iostream>
#include "Game.h"
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

	while (true) {
		game.display();
		cout << "";
		char op = _getch();

		game.move(op);
		system("cls");
	}
	
	return 0;
}