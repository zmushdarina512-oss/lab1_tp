#pragma once
#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>

class Base {
protected:
    std::string name;

public:
    Base();
    Base(const std::string& n);
    Base(const Base& other);
    virtual ~Base();

    std::string getName() const;
    void setName(const std::string& n);

    virtual void print() const = 0;
    virtual std::string type() const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;

    friend std::ostream& operator<<(std::ostream& out, const Base& obj);
};

#endif