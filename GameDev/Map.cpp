#include "Map.h"
#include <iostream>
#include <windows.h>
#include <ctime>


char generate_char()
{
		int char_idx = 1 + rand() % 100;

		if (char_idx < 92) {
			return '_';
		}
		else if (char_idx < 94) {
			return 'E';
		}
		else if (char_idx < 96) {
			return 'a';
		}
		else 
		{
			return 'T';
		}
}

void set_forest(vector<vector<char>>& forest, int player_x, int player_y)
{
	srand(time(nullptr));

	for (int i = 0; i < 14; i++)
	{
		vector <char> row;
		for (int j = 0; j < 25; j++)
		{
			if (i == player_y and j == player_x) {
				row.push_back('P');
			}
			else {
				row.push_back(generate_char());
			}
		}
		forest.push_back(row);
	}
}

void set_beach(vector<vector<char>>& beach, int player_x,int player_y)
{
	srand(time(nullptr));

	// default player_x, player_y = (1,12)

	for (int i = 0; i < 14; i++)
	{
		vector<char> row;

		// int sand = offset + rand() % (12 - 5 + 1);
		int sand = 12 + rand() % 6;
		for (int j = 0; j < 25; j++)
		{
			int enemy_idx = 1 + rand() % 17;

			if (i == player_y and j == player_x) {
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
	set_forest(forest,1,12);
	set_beach(beach,1,12);
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

void Map::reset(int player_x,int player_y)
{
	if (current == 1) {
		forest.clear();
		set_forest(forest,player_x,player_y);
	}
	else if (current == 2) {
		beach.clear();
		set_beach(beach,player_x,player_y);
	};
}


