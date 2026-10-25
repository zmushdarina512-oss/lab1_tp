#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"
#include <stdexcept>
#include <iostream>
#include <limits>

Keeper::Keeper() : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] default constructor\n";
}

Keeper::Keeper(const Keeper& other) : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] copy constructor\n";
    for (int i = 0; i < other.count; ++i) {
        Base* src = other.items[i];
        std::string t = src->type();
        if (t == "Hero") add(new Hero(*(Hero*)src));
        else if (t == "Villain") add(new Villain(*(Villain*)src));
        else if (t == "Monster") add(new Monster(*(Monster*)src));
    }
}

Keeper::~Keeper() {
    std::cout << "[Keeper] destructor\n";
    for (int i = 0; i < count; ++i) delete items[i];
    delete[] items;
}

void Keeper::grow() {
    int newCap = (capacity == 0) ? 4 : capacity * 2;
    Base** newArr = new Base * [newCap];
    for (int i = 0; i < count; ++i) newArr[i] = items[i];
    delete[] items;
    items = newArr;
    capacity = newCap;
}

void Keeper::add(Base* obj) {
    if (!obj) throw std::invalid_argument("Keeper::add: nullptr");
    if (count == capacity) grow();
    items[count++] = obj;
}

void Keeper::removeAt(int index) {
    if (index < 0 || index >= count) throw std::out_of_range("Keeper::removeAt: invalid index");
    delete items[index];
    for (int i = index; i < count - 1; ++i) items[i] = items[i + 1];
    --count;
}

void Keeper::edit(int index) {
    Base* obj = at(index);
    std::string t = obj->type();
    std::string s;

    if (t == "Hero") {
        Hero* h = (Hero*)obj;
        std::cout << "Current name: " << h->getName() << "\nNew name (Enter to keep): ";
        std::getline(std::cin, s); if (!s.empty()) h->setName(s);
        std::cout << "New weapon (Enter to keep): ";
        std::getline(std::cin, s); if (!s.empty()) h->setWeapon(s);
    }
    else if (t == "Villain") {
        Villain* v = (Villain*)obj;
        std::cout << "Current name: " << v->getName() << "\nNew name (Enter to keep): ";
        std::getline(std::cin, s); if (!s.empty()) v->setName(s);
        std::cout << "New crime (Enter to keep): ";
        std::getline(std::cin, s); if (!s.empty()) v->setCrime(s);
    }
    else if (t == "Monster") {
        Monster* m = (Monster*)obj;
        std::cout << "Current name: " << m->getName() << "\nNew name (Enter to keep): ";
        std::getline(std::cin, s); if (!s.empty()) m->setName(s);
        std::cout << "New appearance (Enter to keep): ";
        std::getline(std::cin, s); if (!s.empty()) m->setAppearance(s);
    }
}

int Keeper::size() const { return count; }

Base* Keeper::at(int index) const {
    if (index < 0 || index >= count) throw std::out_of_range("Keeper::at: invalid index");
    return items[index];
}

void Keeper::printAll() const {
    if (count == 0) { std::cout << "Container is empty.\n"; return; }
    for (int i = 0; i < count; ++i) {
        std::cout << "[" << i << "] ";
        items[i]->print();
        std::cout << "---\n";
    }
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) throw std::runtime_error("Could not open file for writing");
    out << count << "\n";
    for (int i = 0; i < count; ++i) items[i]->save(out);
    out.close();
    std::cout << "Saved " << count << " objects to " << filename << "\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) throw std::runtime_error("Could not open file");
    for (int i = 0; i < count; ++i) delete items[i];
    count = 0;

    int n; in >> n; in.ignore();
    if (n < 0) throw std::runtime_error("Corrupted count in file");
    for (int i = 0; i < n; ++i) {
        std::string t; std::getline(in, t);
        Base* obj = nullptr;
        if (t == "Hero") obj = new Hero();
        else if (t == "Villain") obj = new Villain();
        else if (t == "Monster") obj = new Monster();
        else throw std::runtime_error("Unknown type: " + t);
        obj->load(in);
        add(obj);
    }
    in.close();
    std::cout << "Loaded " << count << " objects from " << filename << "\n";
}