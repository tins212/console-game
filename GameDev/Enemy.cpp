#include "Enemy.h"



Enemy::Enemy(int x, int y, int level, int health, int attack, string type)
{
    this->x = x;
    this->y = y;
    this->level = level;
    this->type = type;
    this->health = health;
    this->attack = attack;
}

int Enemy::get_x()
{
    return x;
}

int Enemy::get_y()
{
    return y;
}

int Enemy::get_health()
{
    return health;
}

int Enemy::get_level()
{
    return level;
}

int Enemy::get_attack()
{
    int min_attack = attack - 6;
    int max_attack = attack - 3;

    return min_attack + rand() % (max_attack - min_attack + 1);
}

string Enemy::get_type()
{
    return type;
}

void Enemy::get_damaged(int damage)
{
    health -= damage;
}
