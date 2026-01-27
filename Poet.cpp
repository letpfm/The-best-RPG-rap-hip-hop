#include "Poet.h"
#include <iostream>

Poet::Poet() {
    type = CharacterType::POET;
    level = 1;
    UpdateStats();
    health = maxHealth;
}

void Poet::UpdateStats() {
    maxHealth = 100 + level * 8;
    damage = 10 + level * 2;
    wisdom = 12 + level * 3;
    inspiration = 15 + level * 2;
    skill = "Стихотворение уровня " + std::to_string(level);
}

int Poet::Attack() {
    int bonus = inspiration > 0 ? rand() % inspiration : 0;
    std::cout << name << " пронзает души слогом и наносит " << damage + bonus << " урона!\n";
    return damage + bonus;
}
