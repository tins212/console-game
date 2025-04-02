#pragma once

class Player {
public:
	Player();
	int get_health();
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);
private:
	int health;
	int x;
	int y;
};