#include "Game.h"
#include "Map.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

Game::Game()
{
	game_over = false;
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
		// checks if there is a fight or an obsticale 
		if (can_move(temp_map[player.get_y() - 1][player.get_x()])) {
			// deletes the player from the old location
			temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();
			
			// checks current terrain changed
			if (map.get_current_terrain() != temp_map[player.get_y() - 1][player.get_x()]) {
				map.set_current_terrain(temp_map[player.get_y() - 1][player.get_x()]);
			}

			// sets the player in the next location
			temp_map[player.get_y() - 1][player.get_x()] = 'P';

			// updates player
			player.set_x(player.get_x());
			player.set_y(player.get_y() - 1);
		}
		break;
	case 'A':
		if (can_move(temp_map[player.get_y()][player.get_x() - 1])) {
			temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();

			if (map.get_current_terrain() != temp_map[player.get_y()][player.get_x() - 1]) {
				map.set_current_terrain(temp_map[player.get_y()][player.get_x() - 1]);
			}

			temp_map[player.get_y()][player.get_x() - 1] = 'P';

			player.set_x(player.get_x() - 1);
			player.set_y(player.get_y());
		}
		break;
	case 'D':
		if (can_move(temp_map[player.get_y()][player.get_x() + 1])) {
			
			temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();

			if (map.get_current_terrain() != temp_map[player.get_y()][player.get_x() + 1]) {
				map.set_current_terrain(temp_map[player.get_y()][player.get_x() + 1]);
			}

			temp_map[player.get_y()][player.get_x() + 1] = 'P';

			player.set_x(player.get_x() + 1);
			player.set_y(player.get_y());
		}
		break;
	case 'S':

		if (can_move(temp_map[player.get_y() + 1][player.get_x()])) {
			temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();
			
			if (map.get_current_terrain() != temp_map[player.get_y() + 1][player.get_x()]) {
				map.set_current_terrain(temp_map[player.get_y() + 1][player.get_x()]);
			}

			temp_map[player.get_y() + 1][player.get_x()] = 'P';

			player.set_x(player.get_x());
			player.set_y(player.get_y() + 1);
		}
		break;
	case 'T':
		// deletes the player from the previous map
		temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();

		map.change_current();

		// updates player coordinates for the second map
		player.set_x(1);
		player.set_y(12);

		// sets the player onto the second map
		vector<vector<char>>& new_map = map.get_map();
		new_map[player.get_y()][player.get_x()] = 'P';
	}
}

void Game::display_stats()
{
	cout << "[ HP: " << player.get_health() << "/100 ] ";
	cout << "[ Level: " << player.get_level() << " ] ";
	cout << "[ XP: " << 12 << "/1250 ] " << endl << endl;
}

bool Game::can_move(char next)
{
	if (next == 'E') {
		if (fight()) {
			return true;
		}
		return false;
	}
	else if (next == 'T') {
		return false;
	}

	return true;
}

bool Game::fight()
{
	int enemy_health = 100;
	int enemy_damage;
	int player_damage;

	system("cls");

	while (true) {
		cout << "Player health: " << player.get_health() << "  Enemy health: " << enemy_health << endl;
		cout << "1 = attack" << endl;
		cout << "2 = block" << endl; 
		cout << "3 = flee" << endl << endl;

		cout << "";
		char player_mov = _getch();
		int enemy_mov = 1 + rand() % 2;

		if (player_mov == '1' and enemy_mov == 1) {
			enemy_damage = 10 + rand() % 10;
			player_damage = 10 + rand() % 10;

			cout << "Both player and enemy have attacked" << endl;
			cout << "Enemy took " << enemy_damage << endl;
			cout << "Player took " << player_damage << endl << endl;
		
			player.get_damaged(player_damage);
			enemy_health -= enemy_damage;
		}
		else if (player_mov == '2' and enemy_mov == 2) {
			cout << "Both players have blocked" << endl;
			cout << "No one took damage " << endl << endl;
		}
		else if (player_mov == '2' and enemy_mov == 1) {
			enemy_damage = 8 + rand() % 11;
			
			cout << "Player has blocked and enemy has attacked" << endl;
			cout << "Player took no damage" << endl;
			cout << "Enemy took " << enemy_damage << endl << endl;

			enemy_health -= enemy_damage;
		}
		else if (player_mov == '1' and enemy_mov == 2) {
			player_damage = 8 + rand() % 11;
			
			cout << "Player has attacked and enemy has blocked" << endl;
			cout << "Player took " << player_damage << endl;
			cout << "Enemy took no damage" << endl << endl;

			player.get_damaged(player_damage);
		}
		else if (player_mov == '3') {
			return false;
		}

		if (enemy_health <= 0) {
			cout << "Enemy has been killed" << endl;

			int upper_limit = player.get_xp_limit() * 0.4;
			int lower_limit = player.get_xp_limit() * 0.1;

			int xp = lower_limit + rand() % (upper_limit - lower_limit + 1);
			cout << "+" << xp << " XP" << endl;

			player.inc_xp(xp);

			if (player.get_xp() >= player.get_xp_limit()) {
				cout << "Player has leveled up!";
				player.level_up();
				player.inc_xp_limit();
			}

			this_thread::sleep_for(chrono::seconds(2));
			return true;
		}
		else if (player.get_health() <= 0) {
			player.get_killed();
			cout << "Player has been killed" << endl;
			this_thread::sleep_for(chrono::seconds(2));
			cout << "Game over!" << endl;
			this_thread::sleep_for(chrono::seconds(2));

			game_over = true;

			return false;
		}
		else {
			cout << "Press enter for next round" << endl;
			char next_round = _getch();
		}
		
		system("cls");
	}
}

bool Game::is_game_over()
{
	return game_over;
}
