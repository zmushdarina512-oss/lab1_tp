#include "Base.h"

Base::Base() : name("") {
    std::cout << "[Base] default constructor\n";
}

Base::Base(const std::string& n) : name(n) {
    std::cout << "[Base] parameterized constructor\n";
}

Base::Base(const Base& other) : name(other.name) {
    std::cout << "[Base] copy constructor\n";
}

Base::~Base() {
    std::cout << "[Base] destructor\n";
}

std::string Base::getName() const { return name; }
void Base::setName(const std::string& n) { name = n; }

std::ostream& operator<<(std::ostream& out, const Base& obj) {
    obj.print();
    return out;
}