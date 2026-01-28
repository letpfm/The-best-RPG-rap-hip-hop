#include <iostream>
#include <fstream>
#include <memory>
#include "Character.h"
#include "Reper.h"
#include "Poet.h"
#include "Programmer.h"
#include "Enemy.h"
#include "Battle.h"
#include "Factory.h"  // Подключаем Factory.h для использования CreateCharacter

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");  // Устанавливаем русскую локаль
    srand(static_cast<unsigned int>(time(0)));  // Инициализируем генератор случайных чисел

    unique_ptr<Character> player;  // Умный указатель на игрока
    int storyStep = 0;  // Текущий шаг сюжета

    cout << "1 — Новый персонаж\n2 — Загрузить персонажа\n";  // Меню выбора действия
    int choice;
    cin >> choice;  // Ввод действия

    if (choice == 1) {  // Если выбран новый персонаж
        cout << "Выбери класс:\n1 — Репер\n2 — Поэт\n3 — Программист\n";  // Меню выбора класса
        int x;
        cin >> x;

        CharacterType type = static_cast<CharacterType>(x);  // Преобразуем в тип персонажа
        player = CreateCharacter(type);  // Создаем персонажа

        cin.ignore();  // Игнорируем остаток ввода
        cout << "Введите имя персонажа: ";  // Запрос имени
        string name;
        getline(cin, name);  // Ввод имени
        player->SetName(name);  // Устанавливаем имя персонажа
    }
    else {  // Если выбран вариант загрузки
        ifstream file("save.bin", ios::binary);  // Открываем файл сохранения
        if (!file) {  // Если файл не найден
            cout << "Сохранение не найдено!\n";
            return 0;
        }

        CharacterType type;
        file.read((char*)&type, sizeof(type));  // Читаем тип персонажа
        player = CreateCharacter(type);  // Создаем персонажа
        player->Load(file);  // Загружаем данные персонажа

        int savedStory;
        file.read((char*)&savedStory, sizeof(savedStory));  // Читаем сохраненный шаг сюжета
        storyStep = savedStory;  // Устанавливаем шаг сюжета

        cout << "Сохранение загружено!\n";  // Сообщаем о загрузке
    }

    while (true) {  // Главное меню игры
        cout << "\n=== Меню ===\n1 — Баттл\n2 — Показать персонажа\n3 — Лечение\n4 — Сохранить\n5 — Выход\n";  // Меню
        int action;
        cin >> action;

        if (!cin) {  // Проверка на некорректный ввод
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (action == 1) {  // Если выбран бой
            Enemy enemy("Соперник", 50 + rand() % 30, 5 + rand() % 6);  // Создаем врага
            Battle(*player, enemy, storyStep);  // Запускаем бой
        }
        else if (action == 2) {  // Если показать персонажа
            player->ShowInfo();  // Отображаем информацию о персонаже
        }
        else if (action == 3) {  // Если лечение
            if (player->IsAlive()) {
                player->Heal();  // Восстанавливаем стандартное количество здоровья
            }
            else {
                cout << "Вы не можете лечиться, так как ваш персонаж мёртв.\n";
            }
        }
        else if (action == 4) {  // Если сохранить
            ofstream file("save.bin", ios::binary);  // Открываем файл для сохранения
            CharacterType type = player->GetType();  // Получаем тип персонажа
            file.write((char*)&type, sizeof(type));  // Сохраняем тип
            player->Save(file);  // Сохраняем персонажа
            file.write((char*)&storyStep, sizeof(storyStep));  // Сохраняем шаг сюжета

            if (file.good()) cout << "Сохранено успешно!\n";  // Если сохранение прошло успешно
            else cout << "Ошибка сохранения!\n";  // Если возникла ошибка
        }
        else break;  // Если выбран выход из игры
    }

    return 0;  // Завершение программы
}
