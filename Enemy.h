#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    std::string name;
    int health;
    int damage;

    Enemy(std::string n, int h, int d);
    bool IsAlive() const;
    void TakeDamage(int d);
    int Attack();
};

#endif // ENEMY_H
