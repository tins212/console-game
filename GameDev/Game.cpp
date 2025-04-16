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
	
	switch (op) {
	case 'w':
		update_map(0, -1);
		break;
	case 'a':
		update_map(-1, 0);
		break;
	case 'd':
		update_map(1, 0);
		break;
	case 's':
		update_map(0, 1);
		break;
	case 't':
		travel();
		break;
	case 'n':
		display_skills();
		break;
	}
}

void Game::display_stats()
{
	cout << "[ HP: " << player.get_health() << "/" << player.get_health_limit() << " ] ";
	cout << "[ Level: " << player.get_level() << " ] ";
	cout << "[ XP: " << player.get_xp() << "/" << player.get_xp_limit() << " ] " << endl << endl;
}

void Game::display_skills()
{
	system("cls");
	while (true) {
		cout << "=========================" << endl;
		cout << "    PLAYER STATS MENU   " << endl;
		cout << "=========================" << endl;

		cout << "Max Health  : " << player.get_health_limit() << endl;
		cout << "Level       : " << player.get_level() << endl << endl;

		cout << "Defense	    : " << player.get_defense() << endl;
		cout << "Crit Chance : " << player.get_crit_chance() << "%" << endl;
		cout << "Agility     : " << player.get_agility() << endl;

		cout << "-------------------------" << endl;
		cout << "Press [x] to exit" << endl;

		char user = _getch();
		if (user == 'x') break;

		system("cls");
	}

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
	else if (next == 'a') {
		int to_increase = 5 + rand() % 6;

		if (to_increase + player.get_health() <= 100) {
			player.inc_healh(to_increase);
		}
		else {
			player.inc_healh(100 - player.get_health());
		}
	}

	return true;
}

bool Game::fight()
{
	int enemy_health = 100;
	int enemy_damage;
	int player_damage;

	int round = 1;

	system("cls");

	while (true) {

		cout << "Round: " << round << endl;
		cout << "-------------------------" << endl;

		cout << "|Player HP: "<< player.get_health() << "		|" << endl;
		cout << "|Enemy HP: " << enemy_health << "		|" << endl;
		
		cout << "-------------------------" << endl;

		cout << "|What will you do?	|" << endl;
		cout << "|1. attack		|" << endl;
		cout << "|2. block		|" << endl; 
		cout << "|3. flee		|" << endl;

		cout << "-------------------------" << endl;
		cout << "Action: " << endl;

		char player_mov = _getch();
		int enemy_mov = 1 + rand() % 4;
		
		// main fighting logic
		if (player_mov == '1' and enemy_mov < 4) {
			enemy_damage = 10 + rand() % 10;
			player_damage = 8 + rand() % 10;
			cout << "Both player and enemy have attacked" << endl << endl;

			// crit mechanic
			int crit_chance = 1 + rand() % 100;
			if (crit_chance < player.get_crit_chance()) {
				cout << "Player made a critical hit" << endl;
				player_damage += 1 + rand() % 10;
			}

			cout << "Enemy took " << enemy_damage << endl;
			cout << "Player took " << player_damage << endl << endl;
		
			player.get_damaged(player_damage);
			enemy_health -= enemy_damage;
		}
		else if (player_mov == '2' and enemy_mov == 4) {
			cout << "Both players have blocked" << endl;
			cout << "No one took damage " << endl << endl;
		}
		else if (player_mov == '2' and enemy_mov < 4) {
			enemy_damage = 8 + rand() % 11;
			
			cout << "Player has blocked and enemy has attacked" << endl << endl;

			cout << "Player took no damage" << endl;
			cout << "Enemy took " << enemy_damage << endl << endl;

			enemy_health -= enemy_damage;
		}
		else if (player_mov == '1' and enemy_mov == 4) {
			player_damage = 8 + rand() % 11;
			player_damage += 1 + rand() % (player.get_defense()/2);

			// crit mechanic
			int crit_chance = 1 + rand() % 100;
			if (crit_chance < player.get_crit_chance()) {
				cout << "Player made a critical hit" << endl;
				player_damage += 1 + rand() % 10;
			}

			cout << "Player has attacked and enemy has blocked" << endl;
			cout << "Player took " << player_damage << endl;
			cout << "Enemy took no damage" << endl << endl;

			player.get_damaged(player_damage);
		}
		else if (player_mov == '3') {
			int flee_damage = 1 + rand() % 10;
			int flee = 1 + rand() % 100;

			if (flee > player.get_agility()) {
				cout << "Player has fleed and took " << flee_damage << " damage" << endl;
				player.get_damaged(flee_damage);
			}
			else {
				cout << "Player has fleed and took no damage" << endl;
			}
			this_thread::sleep_for(chrono::seconds(2));
			return false;
		}

		// end of fight logic
		if (enemy_health <= 0) {
			cout << "Enemy has been killed" << endl;

			int upper_limit = player.get_xp_limit() * 0.4;
			int lower_limit = player.get_xp_limit() * 0.1;

			int xp = lower_limit + rand() % (upper_limit - lower_limit + 1);
			cout << "+" << xp << " XP" << endl;

			player.inc_xp(xp);

			if (player.get_xp() >= player.get_xp_limit()) {
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
		
		round++;
		system("cls");
	}
}

bool Game::is_game_over()
{
	return game_over;
}

void Game::slow_down(char current_terrain)
{
	if (current_terrain == 'o') {
		this_thread::sleep_for(chrono::milliseconds(200));
	}
	else if (map.get_current_terrain() == '~') {
		this_thread::sleep_for(chrono::milliseconds(400));
	}
}

void Game::update_map(int x, int y)
{
	if (is_out_of_bounds(x,y)) {
		player.reset_cord();
		map.reset(player.get_x(),player.get_y());
		return;
	}

	vector<vector<char>>& temp_map = map.get_map();
	
	if (can_move(temp_map[player.get_y()+y][player.get_x()+x])) {
		temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();

		if (map.get_current_terrain() != temp_map[player.get_y()+y][player.get_x()+x]
			and temp_map[player.get_y() + y][player.get_x() + x] != 'a'
			) {
			map.set_current_terrain(temp_map[player.get_y()+y][player.get_x()+x]);
		}

		slow_down(map.get_current_terrain());

		temp_map[player.get_y()+y][player.get_x()+x] = 'P';

		player.set_x(player.get_x()+x);
		player.set_y(player.get_y()+y);
	}
}

void Game::travel()
{
	vector<vector<char>>& temp_map = map.get_map();

	// deletes the player from the previous map
	temp_map[player.get_y()][player.get_x()] = map.get_current_terrain();

	map.change_current();

	// updates player coordinates for the second map
	player.reset_cord();

	// sets the player onto the second map
	vector<vector<char>>& new_map = map.get_map();
	new_map[player.get_y()][player.get_x()] = 'P';
}

bool Game::is_out_of_bounds(int x, int y)
{
	int next_x = player.get_x() + x;
	int next_y = player.get_y() + y;

	if (next_y < 0 or next_y > 13 or next_x < 0 or next_x > 24) return true;
	
	return false;
}
