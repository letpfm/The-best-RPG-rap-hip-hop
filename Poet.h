#pragma once
#ifndef POET_H
#define POET_H

#include "Character.h"

class Poet : public Character {
private:
    int wisdom;
    int inspiration;

public:
    Poet();
    void UpdateStats() override;
    int Attack() override;
};

#endif // POET_H
