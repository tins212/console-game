#include "MainMenu.h"

#include <iostream>
#include <conio.h>

MainMenu::MainMenu()
{
	elements.emplace_back("start new game",true);
	elements.emplace_back("load game",false);
	elements.emplace_back("instructions",false);

	// {"start new game",true},{"load game"},{ "instructions",false } 
}

void MainMenu::display()
{
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
			change_selected_element(user);
		}
	}
}

void MainMenu::instructions()
{

	while (true) {
		system("cls");
		cout << "movement up = w" << endl;
		cout << "movement down = a" << endl;
		cout << "movement right = d" << endl;
		cout << "movement left = a" << endl << endl;
		cout << "travel = t" << endl;
		cout << "inventory = i" << endl;
		cout << "shop = p" << endl;
		cout << "stats = n" << endl << endl;

		cout << "press x to go back to menu" << endl;
		char user = _getch();
		if (user == 'x') {
			system("cls");
			return;
		}
	}
}

void MainMenu::change_selected_element(char user)
{
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
