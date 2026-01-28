#pragma once
#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include "Character.h"

class Programmer : public Character {
private:
    int charisma;
    int creativity;
    int wisdom;
    int inspiration;
    int logic;

public:
    Programmer();
    void UpdateStats() override;
    int Attack() override;
};

#endif // PROGRAMMER_H
