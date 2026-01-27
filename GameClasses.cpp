#pragma once
#include "GameClasses.h"

Warrior::Warrior()
{
	name = "воин";
	health = 35;
	damage = 10;
};

Warrior::Warrior(std::string name, unsigned int health, float damage)
{
	cout << "кастомный конструктор война" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
};

void Warrior::GetWeapons()
{
	cout << name << " взял в руки " << weapons[lvl - 1];
};

void Warrior::GetInfo() 
{
	Npc::GetInfo();
	cout << "Сила - " << strenght << endl;
	cout << "Доступное оружие - ";
	for (int i = 0; i < lvl; i++) 
	{
		cout << weapons[i] << endl;
	}
};
void Warrior::Create()
{
	cout << "Вы создали война" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	GetInfo();
	GetWeapons();
};

bool Warrior::operator == (const Warrior& warrior) const
{
	return (warrior.damage == this->damage) &&
		(warrior.health == this->health) &&
		(warrior.strenght == this->strenght);
};

Warrior& Warrior::operator = (const Npc& npc)
{
	if (this != &npc)
	{
		this->name = npc.GetName();
		this->health = npc.GetHealth();
		this->damage = npc.GetDamage();
		this->lvl = npc.GetLvl();
	}

	return *this;
}

bool Warrior::Save()
{
	ofstream saveSystem("save.bin", ios::binary);
	if (saveSystem.is_open())
	{
		if (!Npc::Save())
		{
			cout << "Сохранение не удалось\nПопробуйте позже\n";
			return false;
		}

		saveSystem.write(reinterpret_cast<const char*>(&strenght), sizeof(strenght));
		saveSystem.close();
		return true;
	}
	else
	{
		cout << "Сохранение не удалось\nПопробуйте позже\n";
		return false;
	}
};

bool Warrior::Load()
{
	ifstream loadSystem("save.bin", ios::binary);
	if (loadSystem.is_open())
	{
		if (!Npc::Load())
		{
			cout << "Связь с небесами нарушена\nПамять о ваших прошлых путешествиях повреждена\n";
			return false;
		}
		loadSystem.read(reinterpret_cast<char*>(&strenght), sizeof(strenght));
	}
	else
	{
		cout << "Связь с небесами нарушена\nПамять о ваших прошлых путешествиях повреждена\n";
		return false;
	}
	loadSystem.close();
	return true;
};
Warrior::~Warrior() 
{
	cout << name << " пал смертью храбрых" << endl;
};

Wizard::Wizard()
{
	name = "волшебник";
	health = 23;
	damage = 15;
};

Wizard::Wizard(string name, unsigned int health, float damage)
{
	cout << "кастомный конструктор волшебника" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
};

void Wizard::GetInfo()   
{
	Npc::GetInfo();
	cout << "Интеллект - " << intellect << endl;
	cout << "Доступные заклинания в книге заклинаний - ";
	GetSpellsInfo();
};

void Wizard::GetSpellsInfo()
{
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << " заклинание:\n";
		for (int j = 0; j < 5; j++)
		{
			cout << spells[i][j] << endl;
		}
		cout << endl;
	}
}

void Wizard::Create()
{
	cout << "Вы создали волшебника" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	GetInfo();
};

Wizard Wizard::operator + (const Wizard& wizard) const
{
	return Wizard(
		this->name,
		(this->health + wizard.health),
		(this->damage + wizard.damage)
	);
};

bool Wizard::Save()
{
	if (Npc::Save())
	{
		ofstream saveSystem("save.bin", ios::binary | ios::app); //дозаписываем остальные характеристики
		if (saveSystem.is_open())
		{
			saveSystem.write(reinterpret_cast<const char*>(&intellect), sizeof(intellect));
			for (int i = 0; i < 4; i++)
			{
				//saveSystem.write(reinterpret_cast<const char*>(&spell[i]), sizeof(spell[i]));
			}
			saveSystem.close();
			return true;
		}
		else
		{
			cout << "Сохранение не удалось\nПопробуйте позже\n";
			return false;
		}
	}
};

Wizard::~Wizard()
{
	cout << name << " испустил дух" << endl;
};

Wizard::Spell::Spell(string name, unsigned short damage,
	unsigned short price, bool isCurse , int timeCast)
{
	this->name = name;
	this->damage = damage;
	this->price = price;
	this->isCurse = isCurse;
	this->timeCast = timeCast;
}

string Wizard::Spell::operator[](unsigned index) const
{
	switch (index)
	{
	case 0: return "Название - " + name; break;
	case 1: return "Урон - " + to_string(damage); break;
	case 2: return "Стоимость применения - " + to_string(price) + " маны"; break;
	case 3:
	{
		if (isCurse)
		{
			return "периодичный урон";
		}
		else {
			return "произносимое заклинание";
		}
		break;
	}
	case 4:
		return isCurse ? "Длительность негативного эффекта - " + to_string(timeCast) :
			"Длительность применения - " + to_string(timeCast);
		break;
	default: return "такого свойства заклинания не существует"; break;
	}
}

unsigned short Wizard::Spell::CastSpell()
{
	cout << "Вы применили " << name << " на противнике" << endl;
	return damage;
}

Paladin::Paladin()
{
	name = "паладин";
	health = 25;
	damage = 12;
	strenght = 27;
};

void Paladin::GetInfo()
{
	Warrior::GetInfo();
	cout << "Интеллект - " << intellect << endl;
	cout << "Доступные заклинания в книге заклинаний - ";
	GetSpellsInfo();
};

void Paladin::Create()
{
	cout << "Вы создали паладина" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	GetInfo();
	GetWeapons();
};

bool Paladin::Save()
{
	if (Warrior::Save())
	{
		ofstream saveSystem("save.bin", ios::binary | ios::app);
		if (saveSystem.is_open())
		{
			saveSystem.write(reinterpret_cast<const char*>(&intellect), sizeof(intellect));
			for (int i = 0; i < 4; i++)
			{
				//saveSystem.write(reinterpret_cast<const char*>(&spell[i]), sizeof(spell[i]));
			}
			saveSystem.close();
			return true;
		}
		else
		{
			cout << "Сохранение не удалось\nПопробуйте позже\n";
			return false;
		}
	}
};