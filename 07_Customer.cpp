#pragma once
#include <string>

class Customer {
private:
    std::string name;
    std::string phone;

public:
    Customer() : name("Guest"), phone("0000000000") {}

    Customer(const std::string& name, const std::string& phone) {
        this->name = name;
        this->phone = phone;
    }

    std::string getName() const { return this->name; }
    std::string getPhone() const { return this->phone; }
};
