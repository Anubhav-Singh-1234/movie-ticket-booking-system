#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"

// [OOP: Association - Customer interacts with BookingService]
class BookingService {
private:
    std::vector<Booking> allBookings;
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

    bool areAllSeatsAvailable(const std::vector<ShowSeat*>& seats) const {
        for (const ShowSeat* seat : seats) {
            if (seat == nullptr || !seat->isAvailable()) {
                return false;
            }
        }
        return true;
    }

public:
    BookingService() = default;

    std::vector<ShowSeat*> validateAndSelectSeats(Show& show, const std::vector<std::string>& seatNumbers) {
        std::vector<ShowSeat*> selectedSeats;
        std::vector<std::string> seenSeats;

        for (const std::string& seatNum : seatNumbers) {
            bool isDuplicate = (std::find(seenSeats.begin(), seenSeats.end(), seatNum) != seenSeats.end());
            if (isDuplicate) {
                std::cout << "Error: Duplicate seat " << seatNum << " in selection.\n";
                return {};
            }
            seenSeats.push_back(seatNum);

            ShowSeat* seat = show.findShowSeat(seatNum);
            if (seat == nullptr) {
                std::cout << "Error: Seat " << seatNum << " does not exist.\n";
                return {};
            }
            if (!seat->isAvailable()) {
                std::cout << "Error: Seat " << seatNum << " is already BOOKED.\n";
                return {};
            }
            selectedSeats.push_back(seat);
        }
        return selectedSeats;
    }

    double calculateTotal(const std::vector<ShowSeat*>& seats) const {
        return this->priceCalculator.calculateTotal(seats);
    }

    // [OOP: Runtime Polymorphism - Dynamic invocation via Payment pointer]
    Booking* processBooking(const Customer& customer, Show& show, 
                            const std::vector<ShowSeat*>& seats, Payment& paymentMethod) {
        if (seats.empty() || !areAllSeatsAvailable(seats)) {
            std::cout << "Booking failed: One or more selected seats are unavailable.\n";
            return nullptr;
        }

        double totalAmount = this->priceCalculator.calculateTotal(seats);
        Payment* paymentPtr = &paymentMethod;
        bool paymentSuccess = paymentPtr->pay(totalAmount);

        if (!paymentSuccess) {
            std::cout << "Payment failed! Booking could NOT be confirmed.\n";
            Booking failedBooking(customer, &show, seats, totalAmount);
            failedBooking.markFailed();
            this->allBookings.push_back(failedBooking);
            return nullptr;
        }

        Booking confirmedBooking(customer, &show, seats, totalAmount);
        confirmedBooking.confirmBooking();
        this->allBookings.push_back(confirmedBooking);

        Booking* storedBooking = &this->allBookings.back();
        this->ticketPrinter.printTicket(*storedBooking);
        return storedBooking;
    }

    bool cancelBookingById(const std::string& bookingId) {
        for (Booking& booking : this->allBookings) {
            bool isMatchingId = (booking.getBookingId() == bookingId);
            bool isConfirmed = (booking.getStatus() == BookingStatus::CONFIRMED);
            
            if (isMatchingId && isConfirmed) {
                booking.cancelBooking();
                std::cout << "Booking " << bookingId << " cancelled successfully. Seats are now AVAILABLE.\n";
                return true;
            }
            if (isMatchingId && booking.getStatus() == BookingStatus::CANCELLED) {
                std::cout << "Error: Booking " << bookingId << " is already cancelled.\n";
                return false;
            }
        }
        std::cout << "Error: Confirmed booking with ID " << bookingId << " not found.\n";
        return false;
    }

    void printBookingTicket(const Booking& booking) const {
        this->ticketPrinter.printTicket(booking);
    }

    const std::vector<Booking>& getAllBookings() const {
        return this->allBookings;
    }
};
