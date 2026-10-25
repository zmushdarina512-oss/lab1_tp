#ifndef VILLAIN_H
#define VILLAIN_H
#include "Base.h"

class Villain : public Base {
private:
    std::string weapon;
    std::string crime;
    std::string location;
    std::string* skills;
    int skillsCount;

public:
    Villain();
    Villain(const std::string& n, const std::string& w, const std::string& c, const std::string& loc, const std::string* s, int count);
    Villain(const Villain& other);
    ~Villain();

    std::string getWeapon() const;
    void setWeapon(const std::string& w);
    std::string getCrime() const;
    void setCrime(const std::string& c);
    std::string getLocation() const;
    void setLocation(const std::string& l);
    int getSkillsCount() const;
    std::string getSkill(int i) const;
    void setSkills(const std::string* s, int count);

    void print() const override;
    std::string type() const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
#endif
