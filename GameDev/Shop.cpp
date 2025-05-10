#include "Shop.h"

Shop::Shop()
{
}

void Shop::start(Player& p)
{
	set_shop();

	player = &p;


	while (true) {

	}

}

void Shop::display()
{

}

void Shop::set_shop()
{
	vector <char> row;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j == 0 or j == 5) {
				row.push_back('#');
			}

		}
	}
}
