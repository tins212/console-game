#pragma once
#include "Player.h"
#include "Enemy.h"
#include "sstream"
#include <vector>

using namespace std;

class Fight {
public:
	Fight();

	void start_fight(Player& player, Enemy& enemy);
	int get_result();
private:
	Player* player;
	Enemy* enemy;
	int result;
	int round;
	stringstream action;

	vector <string> actions;
private:
	void display();
	void display_result();

	bool update_stamina(char move_index);
	bool is_move_illegal(char move_index);

	void main_handler(char player_move, int enemy_move);
	void attack_vs_attack_handler();
	void block_vs_attack_handler();
	void attack_vs_block_handler();
	void flee_handler();
	void end_of_fight_handler();
	void wait_handler();

	void player_killed();
	void enemy_killed();
	void enemy_killed_display(int xp, int health, int coins);
};