#pragma once
#include <string>

// [OOP: Abstraction - Abstract class with pure virtual method]
class Payment {
public:
    virtual ~Payment() = default;
    virtual bool pay(double amount) = 0;
    virtual std::string getPaymentMethodName() const = 0;
};
