#include "Battle.h"
#include <iostream>

void Battle(Character& player, Enemy& enemy, int& storyStep) {
    std::cout << "\n=== Баттл: " << player.GetName() << " vs " << enemy.name << " ===\n";

    while (player.IsAlive() && enemy.IsAlive()) {
        std::cout << "\nВыберите действие:\n1 — Атаковать\n2 — Использовать способность\n";
        int choice;
        std::cin >> choice;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            enemy.TakeDamage(player.Attack());
        }
        else {
            std::cout << player.GetName() << " использует " << player.GetSkill() << "!\n";
            enemy.TakeDamage(player.Attack());
        }

        if (enemy.IsAlive()) {
            player.TakeDamage(enemy.Attack());
        }

        std::cout << "Здоровье игрока: " << player.GetHealth() << "/" << player.GetMaxHealth()
            << ", Здоровье врага: " << enemy.health << std::endl;
    }

    if (player.IsAlive()) {
        std::cout << "\n" << player.GetName() << " победил!\n";
        int gainedExp = 20 + rand() % 11;
        std::cout << "Получено опыта: " << gainedExp << std::endl;
        player.GainExp(gainedExp);

        storyStep++;
        switch (storyStep) {
        case 1: std::cout << "После легкой победы над оксимироном вы ощущаете покалывание, мозг растет\n"; break;
        case 2: std::cout << "Эволюция рифм синтезируют квантовый распат панчлайна\n"; break;
        case 3: std::cout << "Вы нашли монетку, но она была приклеена к полу\n"; break;
        case 5: std::cout << "оксимирон вернулся, он забыл куртку\n"; break;
        case 6: std::cout << "это был сильный школьник, жаль, что он забыл текст\n"; break;
        case 7: std::cout << "ведущий отказался выкладывать этот батл\n"; break;
        case 8: std::cout << "бездна может кровоточить, если вы понимаете о чем я\n"; break;
        case 9: std::cout << "они не поняли о чём я\n"; break;
        case 10: std::cout << "каждый новый панч рождает новый сетап, жаль я не знаю английского\n"; break;
        case 11: std::cout << "теперь тебе больше не надо писать реп\n"; break;
        default: std::cout << "очередной баттл прошел изи\n"; break;
        }
    }
    else {
        std::cout << player.GetName() << " проиграл...\n";
    }
}
