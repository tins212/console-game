#pragma once
#include <string>

using namespace std;

class Enemy {
public:
	Enemy(int x, int y, int level, int health, int attack, string type);

	int get_x();
	int get_y();

	int get_health();
	int get_level();
	int get_attack();
	string get_type();

	void get_damaged(int damage);
private:
	int x;
	int y;

	int attack;
	int health;
	int level;
	string type;
};