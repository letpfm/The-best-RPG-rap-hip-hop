#pragma once
#ifndef FACTORY_H
#define FACTORY_H

#include "Character.h"
#include "Reper.h"
#include "Poet.h"
#include "Programmer.h"

// Фабрика для создания персонажей
std::unique_ptr<Character> CreateCharacter(CharacterType type);

#endif // FACTORY_H
