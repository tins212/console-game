#pragma once

class Player {
public:
	Player();
	void set_x(int x);
	void set_y(int y);
	int get_health();
	int get_x();
	int get_y();
	void get_damaged(int d);
	int get_level();
	void get_killed();
	void level_up();
	void inc_xp(int xp);
	int get_xp_limit();
	int get_xp();
	void inc_xp_limit();
private:
	bool is_alive;
	int health;
	int level;
	int xp;
	int xp_limit;
	int x;
	int y;
};