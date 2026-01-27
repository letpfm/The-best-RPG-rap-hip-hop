#pragma once
#include "BaseClasses.h"
#include <string>

class Warrior : public virtual Npc //наследование с модификатором доступа public
{
protected:  //модификатор 0 (приватный - защищенный, доступ к полям, только внутри класса)
	unsigned short strenght{ 31 };
	std::string weapons[4] = { "кастет", "дубинка", "клинок", "меч" };
public:
	Warrior();
	Warrior(std::string name, unsigned int health, float damage);
	void GetWeapons();
	void GetInfo() override;
	void Create() override;
	bool operator == (const Warrior& warrior) const;
	Warrior& operator = (const Npc& npc);
	bool Save() override;
	bool Load() override;
	~Warrior();
};

class Wizard : public virtual Npc
{
public:
	class Spell
	{
		protected: 
			string name{ "заклинание" };
			unsigned short damage{ 0 };
			unsigned short price{ 0 };
			bool isCurse{ false };
			int timeCast{ 0 };
		public:
			Spell(string name = "заклинание", unsigned short damage = 0, unsigned short price = 0, bool isCurse = false, int timeCast = 0);
			string operator[](unsigned index) const;
			unsigned short CastSpell();
	};
protected:
	unsigned short intellect = 27;
	Spell spells[5] = {
		Spell("огненный шар",20,50,false,3),
		Spell("волшебные стрелы",10,30,false,1),
		Spell("ледяной шок",10,20,false),
		Spell("возгорание",10,25,true,5),
		Spell("проклятие",5,10,false,10),
	};
public:
	Wizard();
	Wizard(string name, unsigned int health, float damage);
	void GetInfo() override;
	void Create() override;
	Wizard operator + (const Wizard& wizard) const;
	bool Save() override;
	void GetSpellsInfo();
	~Wizard();
};

class Paladin : public Warrior, public Wizard
{
public:
	Paladin();
	void GetInfo() override;
	void Create() override;
	bool Save() override;

};