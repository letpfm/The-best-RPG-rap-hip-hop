#include "windows.h"
#include <iostream>
#include "GameClasses.h"
#include "BaseClasses.h"
#include "Evil.h"
#include <fstream> 
//используем string, unique_ptr, invalid_argument, setlocale, но не подключили нужные заголовки.
#include <string>
#include <memory>
#include <stdexcept>
#include <clocale>
#include <utility>
using namespace std;

enum class ValueQuality
{
    МУСОР, ОБЫЧНОЕ, РЕДКОЕ, МИФИЧЕСКОЕ, ЛЕГЕНДАРНОЕ 
};

struct Treasure
{
    Treasure() = default;
    string name{ "добыча" };
    ValueQuality quality = ValueQuality::МИФИЧЕСКОЕ;
    unsigned int price{ 0 };
    Treasure(ValueQuality q) : quality(q)
    {
        switch (q)
        {
        case ValueQuality::МУСОР:
            cout << "качество плохое\n";
            break;
        case ValueQuality::ОБЫЧНОЕ:
            cout << "качество средненькое\n";
            break;
        case ValueQuality::РЕДКОЕ:
            cout << "качество хорошее\n";
            break;
        case ValueQuality::МИФИЧЕСКОЕ:
            cout << "качество крутое\n";
            break;
        case ValueQuality::ЛЕГЕНДАРНОЕ:
            cout << "качество идеальное\n";
            break;
        default:
            break;
        }
    }
}; 

struct Cloth : Treasure
{
    Cloth(ValueQuality quality) : Treasure(quality) {}
    string valueSite[5]{ "обувь", "перчатки", "шлем", "нагрудник", "пояс" };
    string site{};
    unsigned short armor{ 1 };
};

enum class CharacterType {
    UNKNOWN = 0,
    WARRIOR,
    WIZARD,
    PALADIN
};

enum class EnemyType {
    КРЕСТЬЯНИН_АНДРЕЙ = 1,
    ЗЛОБНЫЙ_КРОЛИК,
    ЗЕЛИБОБА_С_УЛИЦЫ_СЕЗАМ,
    ГОНЧАР_РОМАНОВ,
    ВАХТЕРША_ЗИНА,
};

unsigned short TestChoise(unsigned short maxChoise, string text)
{
    unsigned short choise = 1;
    cin >> choise;
    while (choise > maxChoise || choise < 1)
    {
        cout << text << endl;
        cin >> choise;
    }
    return choise;
};

// Фабрика для создания персонажей
unique_ptr<Npc> CreateCharacter(CharacterType type)
{
    switch (type)
    {
    case CharacterType::UNKNOWN:
        return make_unique<Npc>();
    case CharacterType::WARRIOR:
        return make_unique<Warrior>();
    case CharacterType::WIZARD:
        return make_unique<Wizard>();
    case CharacterType::PALADIN:
        return make_unique<Paladin>();
    default:
        //для генерации исключения при возникновении ошибки
        throw invalid_argument("Неизвестный тип персонажа");
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    auto player = make_unique<Player>();

    cout << "Привет, путник\nПрисядь у костра и расскажи о себе\nТы впервые тут?\n\t1 - новый персонаж,\n\t2 - загрузить\n";
    if (TestChoise(2, "Наверное ты ошибся, повтори снова") == 1)
    {
        cout << "Расскажи о своих навыках\n\t1 - Воин\n\t2 - Волшебник\n\t3 - Паладин\n";
        unique_ptr<Npc> character = nullptr;
        switch (TestChoise(3, "Такого еще не было в наших краях\nНе мог бы ты повторить"))
        {
            case 1:
                character = CreateCharacter(CharacterType::WARRIOR);
                break;
            case 2: 
                character = CreateCharacter(CharacterType::WIZARD);
                break;
            case 3: 
                character = CreateCharacter(CharacterType::PALADIN);
                break;
        }
        player->Create(move(character));
    }
    else
    {
        ifstream loadSystem("save.txt", ios::binary);
        if (!loadSystem.is_open())
        {
            cout << "Связь с космосом потеряна\nПамять о ваших прошлых путешествиях повреждена\n";
        }
        else
        {
            //реализация загрузки
        }
    }

    //процесс игры

    cout << "Сделаем остановку тут?\n\t1 - сохранить игру\n\t2 - продолжить\n";
    if (TestChoise(2, "Нужно четко определиться с решением\nПовтори свой ответ") == 1)
    {
        if (player->Save()) {
            cout << "Игра успешно сохранена!\n";
        }
        else {
            cout << "Ошибка сохранения.\n";
        }
    }
    return 0;
}