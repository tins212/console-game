#include "Game.h"
#include "Map.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

Game::Game()
{
}

void Game::display()
{
	if (player.get_is_alive()) {
		if (map.draw() == 0 and map.get_current() != 2) {
			this_thread::sleep_for(chrono::seconds(3));
			system("cls");
			cout << "YOU HAVE WON THE GAME\n\nCONGRATULATIONS";
		}
	}
	else {
		map.draw();
		this_thread::sleep_for(chrono::seconds(3));
		system("cls");
		cout << "GAME OVER\n\n";
	}
}

void Game::move(char op)
{
	// returns the reference of a map
	vector<vector<char>>& temp_map = map.get_map();

	char next_terrain = map.get_current_terrain();

	//first check if the move will cause going out of range
	if (move_in_boundaries(op)) {
		switch (op) {
		case 'W':
			// remembering the terrain which we step on
			next_terrain = temp_map[player.get_y() - 1][player.get_x()];

			// checks if there is a fight or an obsticale 
			if (can_move(next_terrain)) {
				// checks current terrain changed
				if (map.get_current_terrain() != next_terrain and next_terrain != 'E') {
					map.set_current_terrain(next_terrain);
				}

				// updates map
				if (next_terrain != 'E') {
					temp_map[player.get_y()][player.get_x()] = next_terrain;
					temp_map[player.get_y() - 1][player.get_x()] = 'P';
				}
				else {
					temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();
					temp_map[player.get_y() - 1][player.get_x()] = 'P';
				}
				
				// updates player
				player.set_x(player.get_x());
				player.set_y(player.get_y() - 1);
			}
			break;
		case 'A':
			// remembering the terrain which we step on
			next_terrain = temp_map[player.get_y()][player.get_x() - 1];

			if (can_move(next_terrain)) {
				// checks current terrain changed
				if (map.get_current_terrain() != next_terrain and next_terrain != 'E') {
					map.set_current_terrain(next_terrain);
				}

				// updates map
				if (next_terrain != 'E') {
					temp_map[player.get_y()][player.get_x()] = next_terrain;
					temp_map[player.get_y()][player.get_x() - 1] = 'P';
				}
				else {
					temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();
					temp_map[player.get_y()][player.get_x() - 1] = 'P';
				}

				// updates player
				player.set_x(player.get_x() - 1);
				player.set_y(player.get_y());
			}
			break;
		case 'D':
			// remembering the terrain which we step on
			next_terrain = temp_map[player.get_y()][player.get_x() + 1];

			if (can_move(next_terrain)) {
				// checks current terrain changed
				if (map.get_current_terrain() != next_terrain and next_terrain != 'E') {
					map.set_current_terrain(next_terrain);
				}

				// updates map
				if (next_terrain != 'E') {
					temp_map[player.get_y()][player.get_x()] = next_terrain;
					temp_map[player.get_y()][player.get_x() + 1] = 'P';
				}
				else {
					temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();
					temp_map[player.get_y()][player.get_x() + 1] = 'P';
				}

				// updates player
				player.set_x(player.get_x() + 1);
				player.set_y(player.get_y());
			}
			break;
		case 'S':
			// remembering the terrain which we step on
			next_terrain = temp_map[player.get_y() + 1][player.get_x()];

			if (can_move(next_terrain)) {
				// checks current terrain changed
				if (map.get_current_terrain() != next_terrain and next_terrain != 'E') {
					map.set_current_terrain(next_terrain);
				}

				// updates map
				if (next_terrain != 'E') {
					temp_map[player.get_y()][player.get_x()] = next_terrain;
					temp_map[player.get_y() + 1][player.get_x()] = 'P';
				}
				else {
					temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();
					temp_map[player.get_y() + 1][player.get_x()] = 'P';
				}

				// updates player
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
}

void Game::display_stats()
{
	cout << "Health: " << player.get_health() << " Level: " << player.get_level() << endl << endl;
}

bool Game::move_in_boundaries(char direction)
{
	if (direction == 'W' and player.get_y() == 0) return false;
	else if (direction == 'A' and player.get_x() == 0) return false;
	else if (direction == 'S' and player.get_y() == 13) return false;
	else if (direction == 'D' and player.get_x() == 24) return false;
	return true;
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
	int enemy_health = 10;
	int enemy_damage = 0;
	int player_damage = 0;

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
			enemy_damage = 1 + rand() % 10;
			player_damage = 3 + rand() % 13;

			cout << "Both player and enemy have attacked" << endl;
			cout << "Player took " << player_damage << endl;
			cout << "Enemy took " << enemy_damage << endl << endl;
		
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

		if (player.get_health() <= 0) {
			player.get_killed();
			cout << "Player has been killed" << endl;
			player.set_health(0);
			this_thread::sleep_for(chrono::seconds(7));
			return false;
		}
		else if (enemy_health <= 0) {
			cout << "Enemy has been killed" << endl;
			this_thread::sleep_for(chrono::seconds(7));
			return true;
		}
		else {
			cout << "Press enter for next round" << endl;
			char next_round = _getch();
		}
		
		system("cls");
	}
}

