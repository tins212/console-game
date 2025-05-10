#include "Fight.h"

Fight::Fight()
{
    result = 0;
    round = 1;
}

void Fight::start_fight(Player& player, Enemy& enemy)
{
    this->player = &player;
    player.reset_defense();
    player.reset_stamina();
    this->enemy = &enemy;

    result = 0;
    round = 1;

    system("cls");
    display();

    while (true) {

        char player_move = _getch();
        int enemy_move = 1 + rand() % 4;
        
        if (!update_stamina(player_move) or is_move_illegal(player_move)) {
            continue;
        }

        // main fight logic
        main_handler(player_move, enemy_move);
        
        // end of fight 
        if (result == 1 or result == 2 or result == 3) {
            break;
        }

        display();

        round++;
    }
}

int Fight::get_result()
{
    return result;
}

void Fight::display()
{
    cout << "Round: " << round << endl << endl;
    cout << "Player:\t\t     " << enemy->get_type() << ":" << endl;
    cout << "HP: " << player->get_health() << "/" << player->get_health_limit() << "\t     HP: " << enemy->get_health() << endl;
    cout << "LEVEL: " << player->get_level() << "\t     LEVEL: " << enemy->get_level() << endl;
    cout << "DEFENSE: " << player->get_defense() << "/" << player->get_defense_limit() << endl;
    cout << "STAMINA: " << player->get_stamina() << "/" << player->get_stamina_limit() << endl;
    cout << "--------------------------------------" << endl;
    cout << "[1] Attack [2] Block [3] Wait [4] Flee" << endl;
    cout << "--------------------------------------" << endl;
}

void Fight::display_result()
{   
    int idx = 0;

    system("cls");
    while (idx != actions.size()) {
        cout << actions[idx] << endl << endl;

        cout << "Press enter to continue" << endl;
        char user = _getch();

        if (user == '\r') {
            idx++;
        }

        system("cls");
    }
}

bool Fight::update_stamina(char move_index)
{   
    // updates stamina each move 
    int current = player->get_stamina();
    int next = 0;

    if (move_index == '1') {
        next = current - 5;
    }
    else if (move_index == '2') {
        next = current - 10;
    }
    else {
        return true;
    }

    if (next >= 0) {
        player->set_stamina(next);
        return true;
    }
    else {
        player->set_stamina(0);
    }
    
    cout << "Player has no stamina" << endl;
    cout << "choose [3] to recharge" << endl;

    return false;
}

bool Fight::is_move_illegal(char move_index)
{
    int ascii_move = int(move_index);

    if (ascii_move >= 49 and ascii_move <= 52) {
        return false;
    }
    return true;
}

void Fight::main_handler(char player_move, int enemy_move)
{
    if (player_move == '1' and enemy_move < 4) {
        attack_vs_attack_handler();
    }
    else if (player_move == '2' and enemy_move == 4) {
        actions.clear();
        actions.push_back("Both players have blocked");
        actions.push_back("No one took damage");
        display_result();
    }
    else if (player_move == '2' and enemy_move < 4) {
        block_vs_attack_handler();
    }
    else if (player_move == '1' and enemy_move == 4) {
        attack_vs_block_handler();
    }
    else if (player_move == '3') {
        wait_handler();
    }
    else if (player_move == '4') {
        flee_handler();
    }

    action.str("");
    action.clear();

    end_of_fight_handler();
}

void Fight::attack_vs_attack_handler()
{
    int enemy_damage = player->get_attack();
    int player_damage = enemy->get_attack();

    actions.clear();
    actions.push_back("Both player and enemy have attacked");

    action.clear();
    action.str("");
    action << "Enemy took " << enemy_damage;
    actions.push_back(action.str());

    action.clear();
    action.str("");
    action << "Player took " << player_damage;
    actions.push_back(action.str());
    
    display_result();

    player->get_damaged(player_damage);
    enemy->get_damaged(enemy_damage);
}

void Fight::block_vs_attack_handler()
{
    int enemy_damage = player->get_attack();

    actions.clear();
    actions.push_back("Player has blocked and enemy has attacked");
    actions.push_back("Player took no damage");

    action.clear();
    action.str("");
    action << "Enemy took " << enemy_damage;
    actions.push_back(action.str());
    display_result();

    enemy->get_damaged(enemy_damage);
}

void Fight::attack_vs_block_handler()
{
    int player_damage = enemy->get_attack();

    actions.clear();
    actions.push_back("Player has attacked and enemy has blocked");

    action.clear();
    action.str("");
    action << "Player took " << player_damage;
    actions.push_back(action.str());

    actions.push_back("Enemy took no damage");
    display_result();

    player->get_damaged(player_damage);
}

void Fight::flee_handler()
{
    int flee_damage = 1 + rand() % 10;
    player->dec_health(flee_damage);

    system("cls");
    cout << "Player has fled " << endl << endl;
    cout <<  "-" << flee_damage << " HP" << endl << endl;
    cout << "press enter to exit";
    
    char user = _getch();

    // Player lost the fight
    result = 2;
}

void Fight::end_of_fight_handler()
{
    if (enemy->get_health() <= 0) {
        enemy_killed();
    }
    else if (player->get_health() <= 0) {
        player_killed();
    }
}

void Fight::wait_handler()
{
    player->inc_stamina();
    action << "Player has gained stamina " << endl;

    int damage = enemy->get_attack() % rand();
    player->get_damaged(damage/2);
    action << "and took " << damage/2 << " damage";

    actions.clear();
    actions.push_back(action.str());
    display_result();
}

void Fight::player_killed()
{
    player->get_killed();
    cout << "Player has been killed" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Game over!" << endl;
    this_thread::sleep_for(chrono::seconds(2));

    result = 3;
}

void Fight::enemy_killed()
{
    int xp = player->get_xp_to_increase();
    player->inc_xp(xp);

    int health = player->get_health_to_increase();
    player->inc_healh(health);

    int coins = 1 + rand() % 10;
    player->inc_coins(coins);

    enemy_killed_display(xp,health,coins);

    if (player->get_xp() >= player->get_xp_limit()) {
        player->level_up();
        player->reset_xp();
        player->inc_xp_limit();
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    result = 1;
}

void Fight::enemy_killed_display(int xp, int health, int coins)
{   
    system("cls");

    cout << "Enemy has been killed" << endl << endl;

    cout << "+" << xp << " XP" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "+" << health << " HP" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "+" << coins << " COINS" << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));

    cout << "press enter to exit" << endl;
    char user = _getch();
}
