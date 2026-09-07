#pragma once
#include <string>
#include <vector>
#include "05_Show.cpp"
#include "07_Customer.cpp"

enum class BookingStatus {
    PENDING,
    CONFIRMED,
    CANCELLED,
    FAILED
};

class Booking {
private:
    // [OOP: Static Member - Shared booking counter for unique IDs]
    static inline int nextBookingIdCounter = 1001;

    std::string bookingId;
    Customer customer;
    const Show* show;
    // [OOP: Aggregation - References ShowSeats]
    std::vector<ShowSeat*> bookedSeats;

    // [OOP: Encapsulation - Private bookingAmount and status]
    double bookingAmount;
    BookingStatus status;

public:
    Booking() 
        : bookingId(""), customer(), show(nullptr), 
          bookingAmount(0.0), status(BookingStatus::PENDING) {}

    Booking(const Customer& customer, const Show* show, 
            const std::vector<ShowSeat*>& seats, double amount) {
        this->bookingId = "BK" + std::to_string(nextBookingIdCounter++);
        this->customer = customer;
        this->show = show;
        this->bookedSeats = seats;
        this->bookingAmount = amount;
        this->status = BookingStatus::PENDING;
    }

    // [OOP Concept: Encapsulation] - State transitions with validation
    void confirmBooking() {
        this->status = BookingStatus::CONFIRMED;
        for (ShowSeat* seat : this->bookedSeats) {
            if (seat != nullptr) {
                seat->bookSeat();
            }
        }
    }

    void cancelBooking() {
        this->status = BookingStatus::CANCELLED;
        for (ShowSeat* seat : this->bookedSeats) {
            if (seat != nullptr) {
                seat->cancelSeat();
            }
        }
    }

    void markFailed() {
        this->status = BookingStatus::FAILED;
        for (ShowSeat* seat : this->bookedSeats) {
            if (seat != nullptr) {
                seat->cancelSeat();
            }
        }
    }

    std::string getBookingId() const { return this->bookingId; }
    const Customer& getCustomer() const { return this->customer; }
    const Show* getShow() const { return this->show; }

    const std::vector<ShowSeat*>& getBookedSeats() const {
        return this->bookedSeats;
    }

    double getBookingAmount() const {
        return this->bookingAmount;
    }

    BookingStatus getStatus() const {
        return this->status;
    }

    std::string getStatusString() const {
        switch (this->status) {
            case BookingStatus::CONFIRMED: return "CONFIRMED";
            case BookingStatus::CANCELLED: return "CANCELLED";
            case BookingStatus::FAILED:    return "FAILED";
            case BookingStatus::PENDING:   return "PENDING";
        }
        return "UNKNOWN";
    }
};
