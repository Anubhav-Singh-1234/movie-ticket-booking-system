#pragma once
#include <string>

enum class SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

constexpr double SILVER_PRICE = 150.0;
constexpr double GOLD_PRICE = 250.0;
constexpr double PLATINUM_PRICE = 400.0;

class Seat {
private:
    std::string seatNumber;
    SeatType seatType;

public:
    // [OOP: Compile-Time Polymorphism - Constructor Overloading]
    Seat() : seatNumber(""), seatType(SeatType::SILVER) {}

    Seat(const std::string& seatNumber, SeatType seatType) {
        // [OOP: this Keyword]
        this->seatNumber = seatNumber;
        this->seatType = seatType;
    }

    std::string getSeatNumber() const { return this->seatNumber; }
    SeatType getSeatType() const { return this->seatType; }

    double getPrice() const {
        if (this->seatType == SeatType::SILVER) {
            return SILVER_PRICE;
        }
        if (this->seatType == SeatType::GOLD) {
            return GOLD_PRICE;
        }
        return PLATINUM_PRICE;
    }

    std::string getSeatTypeString() const {
        if (this->seatType == SeatType::SILVER) {
            return "SILVER";
        }
        if (this->seatType == SeatType::GOLD) {
            return "GOLD";
        }
        return "PLATINUM";
    }
};
