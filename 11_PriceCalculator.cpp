#pragma once
#include <vector>
#include "06_ShowSeat.cpp"

class PriceCalculator {
public:
    PriceCalculator() = default;

    // [OOP: Compile-Time Polymorphism - Method Overloading]
    double calculateTotal(const std::vector<ShowSeat*>& selectedSeats) const {
        double total = 0.0;
        for (const ShowSeat* seat : selectedSeats) {
            if (seat != nullptr) {
                total += seat->getPrice();
            }
        }
        return total;
    }

    double calculateTotal(const std::vector<SeatType>& seatTypes) const {
        double total = 0.0;
        for (SeatType type : seatTypes) {
            if (type == SeatType::SILVER) {
                total += SILVER_PRICE;
            } else if (type == SeatType::GOLD) {
                total += GOLD_PRICE;
            } else if (type == SeatType::PLATINUM) {
                total += PLATINUM_PRICE;
            }
        }
        return total;
    }
};
