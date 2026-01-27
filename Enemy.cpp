#include "Enemy.h"
#include <iostream>

Enemy::Enemy(std::string n, int h, int d) : name(n), health(h), damage(d) {}

bool Enemy::IsAlive() const { return health > 0; }

void Enemy::TakeDamage(int d) { health -= d; if (health < 0) health = 0; }

int Enemy::Attack() {
    std::cout << name << " атакует и наносит " << damage << " урона!\n";
    return damage;
}
