#include "Player.h"

Player::Player()
{
    health = 100;
    health_limit = 100;

    // starting point is at (0,0) in the top left corner
    x = 1;
    y = 12;
    
    level = 1;
    xp = 0;
    xp_limit = 200;
    
    is_alive = true;

    crit_chance = 0;
    agility = 0;
    defense = 10;
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

void Player::reset_cord()
{
    x = 1;
    y = 12;
}

void Player::wrap_cord(int x, int y)
{	
    if (this->y + y < 0) {
        set_y(this->y+12);
    }
    else if (this->y + y > 13) {
        set_y(this->y-12);
    }
    else if (this->x + x < 0) {
        set_x(this->x+22);
    }
    else if (this->x + x > 24) {
        set_x(this->x-22);
    }
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
    system("cls");

    cout << "What would you like to increase?" << endl;
    cout << "1 = health" << endl;
    cout << "2 = crit chance" << endl;
    cout << "3 = defense" << endl;
    cout << "4 = agility" << endl << endl;

    char user = _getch();

    switch (user) {
    case '1':
        inc_health_limit();
        cout << "Current health is " << health << endl;
        break;
    case '2':
        crit_chance += 1;
        cout << "Current crit chance is " << crit_chance << endl;
        break;
    case '3':
        defense += 1;
        cout << "Current defense is " << defense << endl;
        break;
    case '4':
        agility += 1;
        cout << "Current agility is " << agility << endl;
        break;
    }
    level++;
    this_thread::sleep_for(chrono::milliseconds(200));
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

void Player::inc_healh(int inc)
{
    health += inc;
}

void Player::inc_health_limit()
{
    int limit_inc = (health_limit * 0.2);
    health_limit += limit_inc;
}

int Player::get_health_limit()
{
    return health_limit;
}

void Player::inc_crit_chance(int n)
{
    crit_chance += n;
}

void Player::inc_agility(int n)
{
    agility += n;
}

void Player::inc_defense(int n)
{
    defense += n;
}

int Player::get_crit_chance()
{
    return crit_chance;
}

int Player::get_agility()
{
    return agility;
}

int Player::get_defense()
{
    return defense;
}