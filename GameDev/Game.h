#pragma once
#include "Player.h"
#include <vector>

using namespace std;

void generate_map(vector<vector<char>>& map);
char generate_char();

class Game {
public:
	Game();
	void display();
	void move(char op);
private:
	Player player;
	vector<vector<char>> map;
};