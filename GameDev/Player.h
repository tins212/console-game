#pragma once

class Player {
public:
	Player();

	void set_x(int x);
	void set_y(int y);
	int get_x();
	int get_y();
	void reset_cord();
	void wrap_cord(int x, int y);
	
	void get_damaged(int d);
	void get_killed();

	int get_level();
	void level_up();
	
	void inc_xp(int xp);
	int get_xp();
	void inc_xp_limit();
	int get_xp_limit();
	
	void inc_healh(int inc);
	int get_health();
	void inc_health_limit();
	int get_health_limit();
private:
	bool is_alive;

	int health;
	int health_limit;
	
	int level;
	int xp;
	int xp_limit;
	
	int x;
	int y;
};