#pragma once
#include <string>
#include "02_Seat.cpp"

enum class SeatStatus {
    AVAILABLE,
    BOOKED
};

class ShowSeat {
private:
    Seat physicalSeat;
    // [OOP: Encapsulation - Private seatStatus modified via validation methods]
    SeatStatus seatStatus;

public:
    ShowSeat() : physicalSeat(), seatStatus(SeatStatus::AVAILABLE) {}

    explicit ShowSeat(const Seat& physicalSeat) {
        this->physicalSeat = physicalSeat;
        this->seatStatus = SeatStatus::AVAILABLE;
    }

    // [OOP Concept: Encapsulation - Controlled Accessors & Modifiers]
    bool isAvailable() const {
        return this->seatStatus == SeatStatus::AVAILABLE;
    }

    bool bookSeat() {
        if (!isAvailable()) {
            return false; // Rejection if already booked
        }
        this->seatStatus = SeatStatus::BOOKED;
        return true;
    }

    void cancelSeat() {
        this->seatStatus = SeatStatus::AVAILABLE;
    }

    std::string getSeatNumber() const {
        return this->physicalSeat.getSeatNumber();
    }

    SeatType getSeatType() const {
        return this->physicalSeat.getSeatType();
    }

    std::string getSeatTypeString() const {
        return this->physicalSeat.getSeatTypeString();
    }

    double getPrice() const {
        return this->physicalSeat.getPrice();
    }

    std::string getStatusDisplay() const {
        return (this->seatStatus == SeatStatus::BOOKED) ? "[X]" : "[ ]";
    }
};
