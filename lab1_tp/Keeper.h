#ifndef KEEPER_H
#define KEEPER_H
#include "Base.h"
#include <fstream>

class Keeper {
private:
    Base** items;
    int count;
    int capacity;
    void grow();

public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    void add(Base* obj);
    void removeAt(int index);
    void edit(int index);
    int size() const;
    Base* at(int index) const;
    void printAll() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
#endif
