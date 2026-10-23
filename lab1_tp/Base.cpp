#include "Base.h"

Base::Base() : name("") {
    std::cout << "[Base] конструктор по умолчанию\n";
}

Base::Base(const std::string& n) : name(n) {
    std::cout << "[Base] конструктор с параметрами\n";
}

Base::Base(const Base& other) : name(other.name) {
    std::cout << "[Base] конструктор копирования\n";
}

Base::~Base() {
    std::cout << "[Base] деструктор\n";
}

std::string Base::getName() const { return name; }
void Base::setName(const std::string& n) { name = n; }

std::ostream& operator<<(std::ostream& out, const Base& obj) {
    obj.print();
    return out;
}