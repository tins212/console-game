#include "Game.h"
#include "Map.h"

#include <iostream>
#include <vector>

using namespace std;

Game::Game()
{
}

void Game::display()
{
	map.draw();
}

void Game::move(char op)
{
	// returns the reference of a map
	vector<vector<char>>& temp_map = map.get_map();

	switch (op) {
	case 'W':
		// updates map
		temp_map[player.get_y()][player.get_x()] = '_';
		temp_map[player.get_y() - 1][player.get_x()] = 'P';

		// updates player
		player.set_x(player.get_x());
		player.set_y(player.get_y() - 1);
		break;
	case 'A':
		temp_map[player.get_y()][player.get_x()] = '_';
		temp_map[player.get_y()][player.get_x() - 1] = 'P';

		player.set_x(player.get_x() - 1);
		player.set_y(player.get_y());
		break;
	case 'D':
		temp_map[player.get_y()][player.get_x()] = '_';
		temp_map[player.get_y()][player.get_x() + 1] = 'P';

		player.set_x(player.get_x() + 1);
		player.set_y(player.get_y());
		break;
	case 'S':
		temp_map[player.get_y()][player.get_x()] = '_';
		temp_map[player.get_y() + 1][player.get_x()] = 'P';

		player.set_x(player.get_x());
		player.set_y(player.get_y() + 1);
		break;
	case 'T':
		map.change_current();

		// deletes the player from the previous map
		temp_map[player.get_y()][player.get_x()] = '_';
		// updates player coordinates for the second map
		player.set_x(1);
		player.set_y(12);

		vector<vector<char>>& new_map = map.get_map();
		new_map[player.get_y()][player.get_x()] = 'P';
	}
}

