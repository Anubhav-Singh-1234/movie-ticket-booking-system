#pragma once
#include <string>
#include <vector>
#include "02_Seat.cpp"

class Screen {
private:
    std::string screenName;
    // [OOP: Composition - Screen owns its physical seats]
    std::vector<Seat> physicalSeats;

public:
    Screen() : screenName("Default Screen") {}

    explicit Screen(const std::string& screenName) {
        this->screenName = screenName;
    }

    void addSeat(const Seat& seat) {
        this->physicalSeats.push_back(seat);
    }

    std::string getScreenName() const { return this->screenName; }
    const std::vector<Seat>& getPhysicalSeats() const { return this->physicalSeats; }
};
