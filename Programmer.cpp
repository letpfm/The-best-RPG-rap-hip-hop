#include "Programmer.h"
#include <iostream>

Programmer::Programmer() {
    type = CharacterType::PROGRAMMER;
    level = 1;
    UpdateStats();
    health = maxHealth;
}

void Programmer::UpdateStats() {
    maxHealth = 110 + level * 9;
    damage = 12 + level * 3;
    charisma = 8 + level * 2;
    creativity = 8 + level * 2;
    inspiration = 15 + level * 2;
    wisdom = 8 + level * 2;
    logic = 10 + level * 2;
    skill = " одинг уровн€ " + std::to_string(level);
}

int Programmer::Attack() {
    int bonus = logic + inspiration + ((charisma > 0 ? rand() % charisma : 0) + (wisdom > 0 ? rand() % wisdom : 0)) / 2;
    std::cout << name << " извлекает REAL FACTS и наносит " << damage + bonus << " урона!\n";
    return damage + bonus;
}
