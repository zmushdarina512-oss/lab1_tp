#include "Monster.h"

Monster::Monster() : Base(), appearance("") {
    std::cout << "[Monster] default constructor\n";
}
Monster::Monster(const std::string& n, const std::string& app) : Base(n), appearance(app) {
    std::cout << "[Monster] parameterized constructor\n";
}
Monster::Monster(const Monster& other) : Base(other), appearance(other.appearance) {
    std::cout << "[Monster] copy constructor\n";
}
Monster::~Monster() { std::cout << "[Monster] destructor\n"; }

std::string Monster::getAppearance() const { return appearance; }
void Monster::setAppearance(const std::string& a) { appearance = a; }

void Monster::print() const {
    std::cout << "Monster: " << name << "\n  Appearance: " << appearance << "\n";
}
std::string Monster::type() const { return "Monster"; }

void Monster::save(std::ostream& out) const {
    out << "Monster\n" << name << "\n" << appearance << "\n";
}
void Monster::load(std::istream& in) {
    std::getline(in, name); std::getline(in, appearance);
}