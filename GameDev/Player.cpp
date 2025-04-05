#include "Player.h"

Player::Player()
{
    health = 100;
    level = 1;
    // starting point is at (0,0) in the top left corner
    x = 1;
    y = 12;
    xp = 0;
    xp_limit = 200;
    is_alive = true;
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

void Player::get_damaged(int d)
{
    health -= d;
}

int Player::get_level()
{
    return level;
}

void Player::set_x(int x)
{
    this->x = x;
}

void Player::set_y(int y)
{
    this->y = y;
}

void Player::get_killed()
{
    is_alive = false;
}

void Player::level_up()
{
    level++;
}

void Player::inc_xp(int xp)
{
    this->xp += xp;
}

int Player::get_xp_limit()
{
    return xp_limit;
}

int Player::get_xp()
{
    return xp;
}

void Player::inc_xp_limit()
{
    xp_limit += xp_limit * 1.5;
}
