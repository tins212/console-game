#pragma once

class Player {
public:
	Player();
	void set_x(int x);
	void set_y(int y);
	void inc_level();
	int get_health();
	int get_x();
	int get_y();
	void get_damaged(int d);
	int get_level();
	void get_killed();
private:
	bool is_alive;
	int health;
	int level;
	int x;
	int y;
};