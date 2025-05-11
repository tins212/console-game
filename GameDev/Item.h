#pragma once
#include <string>
#include <sstream>

using namespace std;

class Item {
public:
	Item();
	Item(string name,string rarity,int level);
	
	string to_string();
	string get_name();
private:
	string name;
	string rarity;
	int level;
};