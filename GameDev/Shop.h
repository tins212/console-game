#pragma once
#include "Player.h"
#include <vector>

class Shop {
public:
	Shop();

	void start(Player& p);
private:
	void display();
	void set_shop();

	Player* player;
	vector <vector<char>> shop;
};