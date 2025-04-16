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

struct element {
	string name;
	bool is_selected;
};

void instructions() {
	
	while (true) {
		system("cls");
		cout << "MOVEMENT UP = w" << endl;
		cout << "MOVEMENT DOWN = a" << endl;
		cout << "MOVEMENT RIGHT = d" << endl;
		cout << "MOVEMENT LEFT = a" << endl << endl;
		cout << "TRAVEL = t" << endl << endl;

		cout << "PRES x TO GO BACK TO MENU" << endl;
		char user = _getch();
		if (user == 'x') {
			system("cls");
			return;
		}
	}
}

void change_selected_element(vector <element>& elements, char user) {
	if (user == 's') {
		for (int i = 0; i < elements.size(); i++)
		{
			if (elements[i].is_selected) {
				elements[i].is_selected = false;

				if (i + 1 < elements.size()) {
					elements[i + 1].is_selected = true;
				}
				else {
					elements[0].is_selected = true;
				}

				break;
			}
		}
	}
	else if (user == 'w') {
		for (int i = 0; i < elements.size(); i++)
		{
			if (elements[i].is_selected) {
				elements[i].is_selected = false;

				if (i - 1 >= 0) {
					elements[i - 1].is_selected = true;
				}
				else {
					elements[elements.size() - 1].is_selected = true;
				}

				break;
			}
		}
	}
}

void intro() {
	vector <element> elements({ {"start new game",true},{"load game"},{ "instructions",false } });

	while (true) {
		
		// display
		for (int i = 0; i < elements.size(); i++)
		{
			if (elements[i].is_selected) {
				cout << ">> " << elements[i].name << " << " << endl;
			}
			else {
				cout << " " << elements[i].name << endl;
			}
		}
		char user = _getch();
		system("cls");

		if (user == '\r') {
			if (elements[0].is_selected) {
				break;
			}
			else if (elements[2].is_selected) {
				instructions();
			}
		}
		else if (user == 'w' or user == 's') {
			change_selected_element(elements, user);
		}

	}
}

int main() {

	Game game;
	hideCursor();

	intro();

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