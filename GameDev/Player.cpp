#include "Player.h"

Player::Player()
{
    health = 100;
    // starting point is at (0,0) in the top left corner
    x = 1;
    y = 12;
}

int Player::get_health()
{
    return health;
}

int Player::get_x()
{
    return x;
}

int Player::get_y()
{
    return y;
}

void Player::set_x(int x)
{
    this->x = x;
}

void Player::set_y(int y)
{
    this->y = y;
}
