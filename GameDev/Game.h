#pragma once
#include "Player.h"
#include "Map.h"
#include <vector>

using namespace std;

class Game {
public:
	Game();
	void display();
	void move(char op);
private:
	Player player;
	Map map;
};