#include "Map.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

char generate_char_test()
{
		int char_idx = 1 + rand() % 100;

		if (char_idx < 94) {
			return '_';
		}
		else if (char_idx < 96) {
			return 'E';
		}
		else {
			return 'T';
		}
}

void set_forest(vector<vector<char>>& forest)
{
	srand(time(nullptr));

	for (int i = 0; i < 14; i++)
	{
		vector <char> row;
		for (int j = 0; j < 25; j++)
		{
			if (i == 12 and j == 1) {
				row.push_back('P');
			}
			else {
				row.push_back(generate_char_test());
			}
		}
		forest.push_back(row);
	}
}

void set_beach(vector<vector<char>>& beach)
{
	srand(time(nullptr));

	for (int i = 0; i < 14; i++)
	{
		vector<char> row;

		// int sand = offset + rand() % (12 - 5 + 1);
		int sand = 12 + rand() % 6;
		for (int j = 0; j < 25; j++)
		{
			int enemy_idx = 1 + rand() % 17;

			if (i == 12 and j == 1) {
				row.push_back('P');
			}
			else if (enemy_idx == 1) {
				row.push_back('E');
			}
			else if (j < sand) {
				row.push_back('o');
			}
			else {
				row.push_back('~');
			}
		}
		beach.push_back(row);
	}
}

Map::Map()
{
	current = 1;
	current_terrain = '_';
	set_forest(forest);
	set_beach(beach);
}

void Map::draw()
{
	vector<vector<char>> current_map;
	if (current == 1) {
		current_map = forest;
	}
	else {
		current_map = beach;
	}

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			cout << current_map[i][j];
		}
		cout << endl;
	}
}

vector<vector<char>>& Map::get_map()
{
	if (current == 1) {
		return forest;
	}
	else if (current == 2) {
		return beach;
	}
}

void Map::change_current()
{
	system("cls");
	cout << "Where would you like to travel?" << endl;
	cout << "1 = Forest" << endl;
	cout << "2 = Beach" << endl;

	while (true) {

		char choice = _getch();
	
		if (choice == '1' and current != 1) {
			current = 1;
			current_terrain = '_';
			break;
		}
		else if (choice == '2' and current != 2) {
			current = 2;
			current_terrain = 'o';
			break;
		}
		else {
			cout << "Already at the map!" << endl;
		}
	}
}

char Map::get_current_terrain()
{
	return current_terrain;
}

void Map::set_current_terrain(char terrain)
{
	if (terrain != 'E') {
		current_terrain = terrain;
	}
}


