#include "Factory.h"

std::unique_ptr<Character> CreateCharacter(CharacterType type) {
    switch (type) {
    case CharacterType::REPER:
        return std::make_unique<Reper>();
    case CharacterType::POET:
        return std::make_unique<Poet>();
    case CharacterType::PROGRAMMER:
        return std::make_unique<Programmer>();
    default:
        return nullptr;
    }
}
