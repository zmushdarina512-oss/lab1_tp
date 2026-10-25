#include <iostream>
#include <string>
#include <limits>
#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"

std::string askString(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int askInt(const std::string& prompt) {
    std::cout << prompt;
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cout << "Input error, try again: ";
    }
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    return x;
}

void askSkills(std::string*& arr, int& n) {
    n = askInt("How many skills? ");
    if (n < 0) { n = 0; arr = nullptr; return; }
    arr = n ? new std::string[n] : nullptr;
    for (int i = 0; i < n; ++i) {
        std::cout << "  Skill #" << (i + 1) << ": ";
        std::getline(std::cin, arr[i]);
    }
}

int main() {
    try {
        Keeper keeper;
        while (true) {
            std::cout << "\n==== MENU ====\n";
            std::cout << "1 - Add Hero\n2 - Add Villain\n3 - Add Monster\n";
            std::cout << "4 - Show all\n5 - Remove by index\n6 - Edit by index\n";
            std::cout << "7 - Save to file\n8 - Load from file\n0 - Exit\n";
            std::cout << "Choice: ";
            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                std::cout << "Incorrect input.\n";
                continue;
            }
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

            if (choice == 0) break;

            try {
                if (choice == 1) {
                    std::string n = askString("Hero name: ");
                    std::string w = askString("Weapon: ");
                    std::string* sk = nullptr; int cnt = 0;
                    askSkills(sk, cnt);
                    keeper.add(new Hero(n, w, sk, cnt));
                    delete[] sk;
                }
                else if (choice == 2) {
                    std::string n = askString("Villain name: ");
                    std::string w = askString("Weapon: ");
                    std::string c = askString("Crime: ");
                    std::string loc = askString("Location: ");
                    std::string* sk = nullptr; int cnt = 0;
                    askSkills(sk, cnt);
                    keeper.add(new Villain(n, w, c, loc, sk, cnt));
                    delete[] sk;
                }
                else if (choice == 3) {
                    std::string n = askString("Monster name: ");
                    std::string a = askString("Appearance: ");
                    keeper.add(new Monster(n, a));
                }
                else if (choice == 4) keeper.printAll();
                else if (choice == 5) keeper.removeAt(askInt("Index to remove: "));
                else if (choice == 6) keeper.edit(askInt("Index to edit: "));
                else if (choice == 7) keeper.saveToFile(askString("Filename: "));
                else if (choice == 8) keeper.loadFromFile(askString("Filename: "));
                else std::cout << "No such option.\n";
            }
            catch (const std::exception& e) {
                std::cout << "ERROR: " << e.what() << "\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "CRITICAL ERROR: " << e.what() << "\n";
    }
    return 0;
}