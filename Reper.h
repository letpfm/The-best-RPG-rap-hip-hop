#pragma once
#ifndef REPER_H
#define REPER_H

#include "Character.h"

class Reper : public Character {
private:
    int charisma;
    int creativity;

public:
    Reper();
    void UpdateStats() override;
    int Attack() override;
};

#endif // REPER_H
