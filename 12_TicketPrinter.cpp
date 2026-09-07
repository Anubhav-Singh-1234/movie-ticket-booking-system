#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "08_Booking.cpp"

class TicketPrinter {
public:
    TicketPrinter() = default;

    void printTicket(const Booking& booking) const {
        std::cout << "\n================ TICKET ================" << "\n";
        std::cout << std::left << std::setw(11) << "Booking ID" << ": " << booking.getBookingId() << "\n";
        
        if (booking.getShow() != nullptr && booking.getShow()->getMovie() != nullptr) {
            std::cout << std::left << std::setw(11) << "Movie" << ": " 
                      << booking.getShow()->getMovie()->getTitle() << "\n";
            std::cout << std::left << std::setw(11) << "Screen" << ": " 
                      << booking.getShow()->getScreen()->getScreenName() << "   " 
                      << booking.getShow()->getStartTime() << "\n";
        }

        std::cout << std::left << std::setw(11) << "Seats" << ": ";
        const auto& seats = booking.getBookedSeats();
        for (size_t i = 0; i < seats.size(); ++i) {
            if (seats[i] != nullptr) {
                std::cout << seats[i]->getSeatNumber();
                if (i + 1 < seats.size()) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << "\n";

        std::cout << std::left << std::setw(11) << "Amount" << ": Rs." 
                  << static_cast<int>(booking.getBookingAmount())
                  << "     Status: " << booking.getStatusString() << "\n";
        std::cout << "========================================" << "\n";
    }
};
