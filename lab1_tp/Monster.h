#ifndef MONSTER_H
#define MONSTER_H
#include "Base.h"

class Monster : public Base {
private:
    std::string appearance;

public:
    Monster();
    Monster(const std::string& n, const std::string& app);
    Monster(const Monster& other);
    ~Monster();

    std::string getAppearance() const;
    void setAppearance(const std::string& a);

    void print() const override;
    std::string type() const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
#endif