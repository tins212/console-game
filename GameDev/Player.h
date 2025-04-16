#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <thread>

using namespace std;

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

	void inc_crit_chance(int n);
	void inc_agility(int n);
	void inc_defense(int n);
	int get_crit_chance();
	int get_agility();
	int get_defense();

private:
	bool is_alive;

	int health;
	int health_limit;
	
	int level;
	int xp;
	int xp_limit;
	
	int x;
	int y;

	int crit_chance;
	int agility;
	int defense;
};