#ifndef HERO_H
#define HERO_H

#include "Base.h"

class Hero : public Base {
private:
    std::string weapon;
    std::string* skills;
    int skillsCount;

public:
    Hero();
    Hero(const std::string& n, const std::string& w, const std::string* s, int count);
    Hero(const Hero& other);
    ~Hero();

    std::string getWeapon() const;
    void setWeapon(const std::string& w);
    int getSkillsCount() const;
    std::string getSkill(int i) const;
    void setSkills(const std::string* s, int count);

    void print() const override;
    std::string type() const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

#endif