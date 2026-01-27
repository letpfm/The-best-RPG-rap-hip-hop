#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <fstream>
#include <limits>
#include <iostream>

enum class CharacterType { REPER = 1, POET, PROGRAMMER };

class Character {
protected:
    std::string name;
    CharacterType type;
    int level;
    int exp;
    int health;
    int maxHealth;
    int damage;
    int healingAmount;
    std::string skill;

public:
    Character();
    virtual ~Character() = default;

    void SetName(const std::string& n);
    std::string GetName() const;
    CharacterType GetType() const;
    int GetLevel() const;
    std::string GetSkill() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    bool IsAlive() const;
    void TakeDamage(int dmg);
    void Heal();
    void Heal(int amount);

    virtual void ShowInfo();
    virtual std::string GetTypeName() const;
    virtual int LevelUpExp() const;
    virtual void GainExp(int e);
    virtual void UpdateStats() = 0;
    virtual int Attack() = 0;

    virtual bool Save(std::ofstream& file);
    virtual bool Load(std::ifstream& file);
};

#endif // CHARACTER_H
