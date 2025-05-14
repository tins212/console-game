#pragma once
#include <vector>
#include <string>

using namespace std;

struct Element {
	string name;
	bool is_selected;

	Element(string name, bool is_selected) : name(name), is_selected(is_selected) {};
};

class MainMenu {
public:
	MainMenu();
	void display();
private:
	void instructions();
	void change_selected_element(char user);

private:
	vector <Element> elements;
};