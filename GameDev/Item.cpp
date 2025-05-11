#include "Item.h"

Item::Item()
{
	name = "";
	rarity = "";
	level = 0;
}

Item::Item(string name, string rarity, int level)
{
	this->name = name;
	this->rarity = rarity;
	this->level = level;
}

string Item::to_string()
{
	stringstream ss;

	ss << "Name: " << name << endl 
	   << "Rarity: " << rarity << endl 
	   << "Level: " << level << endl;

	return ss.str();
}

string Item::get_name()
{
	return name;
}
