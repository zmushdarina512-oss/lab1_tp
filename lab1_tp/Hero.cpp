#include "Hero.h"
#include <stdexcept>

Hero::Hero() : Base(), weapon(""), skills(nullptr), skillsCount(0) {
    std::cout << "[Hero] default constructor\n";
}

Hero::Hero(const std::string& n, const std::string& w, const std::string* s, int count)
    : Base(n), weapon(w), skills(nullptr), skillsCount(0) {
    std::cout << "[Hero] parameterized constructor\n";
    setSkills(s, count);
}

Hero::Hero(const Hero& other) : Base(other), weapon(other.weapon), skills(nullptr), skillsCount(0) {
    std::cout << "[Hero] copy constructor\n";
    setSkills(other.skills, other.skillsCount);
}

Hero::~Hero() {
    std::cout << "[Hero] destructor\n";
    delete[] skills;
}

std::string Hero::getWeapon() const { return weapon; }
void Hero::setWeapon(const std::string& w) { weapon = w; }
int Hero::getSkillsCount() const { return skillsCount; }

std::string Hero::getSkill(int i) const {
    if (i < 0 || i >= skillsCount)
        throw std::out_of_range("Hero::getSkill: invalid skill index");
    return skills[i];
}

void Hero::setSkills(const std::string* s, int count) {
    if (count < 0) throw std::invalid_argument("Hero::setSkills: negative skill count");
    delete[] skills;
    skillsCount = count;
    if (count == 0) { skills = nullptr; return; }
    skills = new std::string[count];
    for (int i = 0; i < count; ++i) skills[i] = s[i];
}

void Hero::print() const {
    std::cout << "Hero: " << name << "\n  Weapon: " << weapon << "\n  Skills (" << skillsCount << "):\n";
    for (int i = 0; i < skillsCount; ++i) std::cout << "    - " << skills[i] << "\n";
}

std::string Hero::type() const { return "Hero"; }

void Hero::save(std::ostream& out) const {
    out << "Hero\n" << name << "\n" << weapon << "\n" << skillsCount << "\n";
    for (int i = 0; i < skillsCount; ++i) out << skills[i] << "\n";
}

void Hero::load(std::istream& in) {
    std::getline(in, name);
    std::getline(in, weapon);
    int cnt; in >> cnt; in.ignore();
    if (cnt < 0) throw std::runtime_error("Hero::load: corrupted data in file");
    delete[] skills;
    skillsCount = cnt;
    if (cnt == 0) { skills = nullptr; return; }
    skills = new std::string[cnt];
    for (int i = 0; i < cnt; ++i) std::getline(in, skills[i]);
}