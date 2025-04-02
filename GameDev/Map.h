#pragma once
#include <vector>

using namespace std;

char generate_char_test();
void set_forest(vector<vector<char>>& forest);
void set_beach(vector <vector<char>>& beach);

class Map {
public:
	Map();
	void draw();
	vector<vector<char>>& get_map();
	void change_current();
private:
	vector<vector<char>> forest;
	vector<vector<char>> beach;
	int current;
};