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
	bool move_in_boundaries(char direction);
	bool can_move(char next);
	bool fight();
private:
	Player player;
	Map map;
};