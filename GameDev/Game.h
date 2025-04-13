#pragma once
#include "Player.h"
#include "Map.h"
#include <conio.h>

using namespace std;

class Game {
public:
	Game();
	void display();
	void move(char op);
	void display_stats();
	bool can_move(char next);
	bool fight();
	bool is_game_over();
private:
	bool game_over;
	Player player;
	Map map;
private:
	void slow_down(char current_terrain);
	void update_map(int x, int y);
	void travel();
	bool is_out_of_bounds(int x, int y);
};