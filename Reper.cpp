#include "Reper.h"
#include <iostream>

Reper::Reper() {
    type = CharacterType::REPER;
    level = 1;
    UpdateStats();
    health = maxHealth;
}

void Reper::UpdateStats() {
    maxHealth = 120 + level * 10;
    damage = 15 + level * 3;
    charisma = 10 + level * 2;
    creativity = 10 + level * 2;
    skill = "Флоу уровня " + std::to_string(level);
}

int Reper::Attack() {
    int bonus = creativity > 0 ? rand() % creativity : 0;
    std::cout << name << " граймит и наносит " << damage + bonus << " урона!\n";
    return damage + bonus;
}
