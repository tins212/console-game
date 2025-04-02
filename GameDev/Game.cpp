#include "Game.h"
#include <iostream>
#include <ctime>

using namespace std;

char generate_char()
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

void generate_map(vector<vector<char>>& map)
{
	for (int i = 0; i < 14; i++)
	{
		vector <char> row;
		for (int j = 0; j < 25; j++)
		{
			if (i == 12 and j == 1) {
				row.push_back('P');
			}
			else {
				row.push_back(generate_char());
			}
		}
		map.push_back(row);
	}
}

Game::Game()
{
	srand(time(nullptr));
	generate_map(map);
}

void Game::display()
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

void Game::move(char op)
{
	switch (op) {
	case 'W':
		// updates map
		map[player.get_y()][player.get_x()] = '_';
		map[player.get_y()-1][player.get_x()] = 'P';
	
		// updates player
		player.set_x(player.get_x());
		player.set_y(player.get_y() - 1);
		break;
	case 'A':
		map[player.get_y()][player.get_x()] = '_';
		map[player.get_y()][player.get_x()-1] = 'P';

		player.set_x(player.get_x()-1);
		player.set_y(player.get_y());
		break;
	case 'D':
		map[player.get_y()][player.get_x()] = '_';
		map[player.get_y()][player.get_x()+1] = 'P';

		player.set_x(player.get_x()+1);
		player.set_y(player.get_y());
		break;
	case 'S':
		map[player.get_y()][player.get_x()] = '_';
		map[player.get_y()+1][player.get_x()] = 'P';

		player.set_x(player.get_x());
		player.set_y(player.get_y()+1);
		break;
	}
}

