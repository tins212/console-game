#pragma once
#include <vector>
#include <conio.h>


using namespace std;

char generate_char();
void set_forest(vector<vector<char>>& forest,int player_x,int player_y);
void set_beach(vector <vector<char>>& beach,int player_x, int player_y);

class Map {
public:
	Map();
	void draw();
	vector<vector<char>>& get_map();

	void change_current();
	int get_current();
	char get_current_terrain();
	void set_current_terrain(char c);

	void reset(int player_x,int player_y);
private:
	vector<vector<char>> forest;
	vector<vector<char>> beach;
	
	int current;
	char current_terrain;
};