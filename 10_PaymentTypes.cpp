#pragma once
#include <iostream>
#include <string>
#include "09_Payment.cpp"

// [OOP: Inheritance - Concrete classes inherit from abstract Payment]
class UpiPayment : public Payment {
private:
    std::string upiId;
    bool simulateSuccess;

public:
    UpiPayment() : upiId("user@bank"), simulateSuccess(true) {}

    UpiPayment(const std::string& upiId, bool simulateSuccess = true) {
        this->upiId = upiId;
        this->simulateSuccess = simulateSuccess;
    }

    // [OOP: Runtime Polymorphism - Dynamic override]
    bool pay(double amount) override {
        if (!this->simulateSuccess || this->upiId == "fail") {
            std::cout << "[UPI] Payment of Rs." << static_cast<int>(amount) 
                      << " via " << this->upiId << " FAILED!\n";
            return false;
        }
        std::cout << "[UPI] Rs." << static_cast<int>(amount) << " paid successfully\n";
        return true;
    }

    std::string getPaymentMethodName() const override {
        return "UPI (" + this->upiId + ")";
    }
};

class CardPayment : public Payment {
private:
    std::string cardNumber;
    bool simulateSuccess;

public:
    CardPayment() : cardNumber("XXXX-XXXX-XXXX-0000"), simulateSuccess(true) {}

    CardPayment(const std::string& cardNumber, bool simulateSuccess = true) {
        this->cardNumber = cardNumber;
        this->simulateSuccess = simulateSuccess;
    }

    bool pay(double amount) override {
        if (!this->simulateSuccess || this->cardNumber == "fail") {
            std::cout << "[CARD] Payment of Rs." << static_cast<int>(amount) 
                      << " via Card ending in " << this->cardNumber << " FAILED!\n";
            return false;
        }
        std::cout << "[CARD] Rs." << static_cast<int>(amount) << " paid successfully\n";
        return true;
    }

    std::string getPaymentMethodName() const override {
        return "Card (" + this->cardNumber + ")";
    }
};

class CashPayment : public Payment {
private:
    bool simulateSuccess;

public:
    explicit CashPayment(bool simulateSuccess = true) {
        this->simulateSuccess = simulateSuccess;
    }

    bool pay(double amount) override {
        if (!this->simulateSuccess) {
            std::cout << "[CASH] Cash payment of Rs." << static_cast<int>(amount) 
                      << " was rejected by cashier!\n";
            return false;
        }
        std::cout << "[CASH] Rs." << static_cast<int>(amount) << " received at counter successfully\n";
        return true;
    }

    std::string getPaymentMethodName() const override {
        return "Cash";
    }
};
