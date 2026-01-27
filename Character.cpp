#include "Character.h"

Character::Character() : 
    level(1), 
    exp(0), 
    health(100), 
    maxHealth(100), 
    damage(10),
    healingAmount(10){}

void Character::SetName(const std::string& n) { name = n; }
std::string Character::GetName() const { return name; }
CharacterType Character::GetType() const { return type; }
int Character::GetLevel() const { return level; }
std::string Character::GetSkill() const { return skill; }
int Character::GetHealth() const { return health; }
int Character::GetMaxHealth() const { return maxHealth; }
bool Character::IsAlive() const { return health > 0; }

void Character::TakeDamage(int dmg) { health -= dmg; if (health < 0) health = 0; }

void Character::Heal() {
    health += healingAmount;  // Восстанавливаем здоровье на значение healingAmount
    if (health > maxHealth) {
        health = maxHealth;  // Если здоровье превышает максимум, устанавливаем на максимальное
    }
    std::cout << name << " восстановил " << healingAmount << " здоровья!\n";
}

void Character::Heal(int amount) {
    if (!IsAlive()) {
        std::cout << name << " мёртв и не может лечиться!\n";
        return;
    }
    health += amount;
    if (health > maxHealth) health = maxHealth;
    std::cout << name << " восстанавливает " << amount << " здоровья (текущее: " << health << "/" << maxHealth << ")\n";
}

void Character::ShowInfo() {
    std::cout << "Класс: " << GetTypeName() << "\n";
    std::cout << "Имя: " << name << "\n";
    std::cout << "Уровень: " << level << "\n";
    std::cout << "Здоровье: " << health << "/" << maxHealth << "\n";
    std::cout << "Урон: " << damage << "\n";
    std::cout << "Навык: " << skill << "\n";
    std::cout << "Опыт: " << exp << "/" << LevelUpExp() << "\n";
}

std::string Character::GetTypeName() const {
    switch (type) {
    case CharacterType::REPER: return "Репер";
    case CharacterType::POET: return "Поэт";
    case CharacterType::PROGRAMMER: return "Программист";
    default: return "Неизвестно";
    }
}

int Character::LevelUpExp() const { return 50 * level; }

void Character::GainExp(int e) {
    exp += e;
    while (exp >= LevelUpExp()) {
        exp -= LevelUpExp();
        level++;
        UpdateStats();
        std::cout << name << " достиг уровня " << level << "!\n";
    }
}

bool Character::Save(std::ofstream& file) {
    uint64_t len = name.size();
    file.write((char*)&len, sizeof(len));
    file.write(name.c_str(), len);
    file.write((char*)&level, sizeof(level));
    file.write((char*)&exp, sizeof(exp));
    file.write((char*)&health, sizeof(health));
    file.write((char*)&maxHealth, sizeof(maxHealth));
    file.write((char*)&damage, sizeof(damage));
    uint64_t skillLen = skill.size();
    file.write((char*)&skillLen, sizeof(skillLen));
    file.write(skill.c_str(), skillLen);
    return file.good();
}

bool Character::Load(std::ifstream& file) {
    uint64_t len;
    file.read((char*)&len, sizeof(len));
    name.resize(len);
    file.read(&name[0], len);
    file.read((char*)&level, sizeof(level));
    file.read((char*)&exp, sizeof(exp));
    file.read((char*)&health, sizeof(health));
    file.read((char*)&maxHealth, sizeof(maxHealth));
    file.read((char*)&damage, sizeof(damage));
    uint64_t skillLen;
    file.read((char*)&skillLen, sizeof(skillLen));
    skill.resize(skillLen);
    file.read(&skill[0], skillLen);
    UpdateStats();
    return file.good();
}
