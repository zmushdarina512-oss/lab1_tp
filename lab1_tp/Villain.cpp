#include "Villain.h"
#include <stdexcept>

Villain::Villain() : Base(), weapon(""), crime(""), location(""), skills(nullptr), skillsCount(0) {
    std::cout << "[Villain] default constructor\n";
}

Villain::Villain(const std::string& n, const std::string& w, const std::string& c, const std::string& loc, const std::string* s, int count)
    : Base(n), weapon(w), crime(c), location(loc), skills(nullptr), skillsCount(0) {
    std::cout << "[Villain] parameterized constructor\n";
    setSkills(s, count);
}

Villain::Villain(const Villain& other)
    : Base(other), weapon(other.weapon), crime(other.crime), location(other.location), skills(nullptr), skillsCount(0) {
    std::cout << "[Villain] copy constructor\n";
    setSkills(other.skills, other.skillsCount);
}

Villain::~Villain() {
    std::cout << "[Villain] destructor\n";
    delete[] skills;
}

std::string Villain::getWeapon() const { return weapon; }
void Villain::setWeapon(const std::string& w) { weapon = w; }
std::string Villain::getCrime() const { return crime; }
void Villain::setCrime(const std::string& c) { crime = c; }
std::string Villain::getLocation() const { return location; }
void Villain::setLocation(const std::string& l) { location = l; }
int Villain::getSkillsCount() const { return skillsCount; }

std::string Villain::getSkill(int i) const {
    if (i < 0 || i >= skillsCount) throw std::out_of_range("Villain::getSkill: invalid index");
    return skills[i];
}

void Villain::setSkills(const std::string* s, int count) {
    if (count < 0) throw std::invalid_argument("Villain::setSkills: negative count");
    delete[] skills;
    skillsCount = count;
    if (count == 0) { skills = nullptr; return; }
    skills = new std::string[count];
    for (int i = 0; i < count; ++i) skills[i] = s[i];
}

void Villain::print() const {
    std::cout << "Villain: " << name << "\n  Weapon: " << weapon << "\n  Crime: " << crime << "\n  Location: " << location << "\n  Skills (" << skillsCount << "):\n";
    for (int i = 0; i < skillsCount; ++i) std::cout << "    - " << skills[i] << "\n";
}

std::string Villain::type() const { return "Villain"; }

void Villain::save(std::ostream& out) const {
    out << "Villain\n" << name << "\n" << weapon << "\n" << crime << "\n" << location << "\n" << skillsCount << "\n";
    for (int i = 0; i < skillsCount; ++i) out << skills[i] << "\n";
}

void Villain::load(std::istream& in) {
    std::getline(in, name); std::getline(in, weapon); std::getline(in, crime); std::getline(in, location);
    int cnt; in >> cnt; in.ignore();
    if (cnt < 0) throw std::runtime_error("Villain::load: corrupted data");
    delete[] skills;
    skillsCount = cnt;
    if (cnt == 0) { skills = nullptr; return; }
    skills = new std::string[cnt];
    for (int i = 0; i < cnt; ++i) std::getline(in, skills[i]);
}