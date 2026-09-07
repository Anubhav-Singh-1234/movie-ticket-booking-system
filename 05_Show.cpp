#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"

class Show {
private:
    int showId;
    // [OOP: Aggregation - Show references Movie and Screen]
    const Movie* movie;
    const Screen* screen;
    std::string startTime;
    // [OOP: Composition - Show owns its ShowSeats]
    std::vector<ShowSeat> showSeats;

    void initializeShowSeats() {
        if (this->screen == nullptr) return;
        for (const Seat& physicalSeat : this->screen->getPhysicalSeats()) {
            this->showSeats.emplace_back(physicalSeat);
        }
    }

public:
    Show() : showId(0), movie(nullptr), screen(nullptr), startTime("") {}

    Show(int showId, const Movie* movie, const Screen* screen, const std::string& startTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
        initializeShowSeats();
    }

    int getShowId() const {
        return this->showId;
    }

    const Movie* getMovie() const {
        return this->movie;
    }

    const Screen* getScreen() const {
        return this->screen;
    }

    std::string getStartTime() const {
        return this->startTime;
    }

    std::vector<ShowSeat>& getShowSeats() {
        return this->showSeats;
    }

    const std::vector<ShowSeat>& getShowSeats() const {
        return this->showSeats;
    }

    ShowSeat* findShowSeat(const std::string& seatNumber) {
        for (ShowSeat& seat : this->showSeats) {
            if (seat.getSeatNumber() == seatNumber) {
                return &seat;
            }
        }
        return nullptr;
    }

    // Displays the visual seat layout adhering to demo output format
    void displaySeatLayout() const {
        std::string upperScreen = this->screen->getScreenName();
        for (char& c : upperScreen) c = static_cast<char>(std::toupper(c));

        std::cout << "\n" << upperScreen << "  "
                  << this->startTime << " | " << this->movie->getTitle() << "\n";

        printTierSeats("SILVER", SeatType::SILVER);
        printTierSeats("GOLD", SeatType::GOLD);
        printTierSeats("PLATINUM", SeatType::PLATINUM);

        std::cout << "\n( [ ] = available   [X] = booked )\n";
    }

private:
    void printTierSeats(const std::string& tierLabel, SeatType tier) const {
        std::cout << std::left << std::setw(10) << tierLabel;
        for (const ShowSeat& seat : this->showSeats) {
            if (seat.getSeatType() == tier) {
                std::cout << seat.getSeatNumber() << seat.getStatusDisplay() << " ";
            }
        }
        std::cout << "\n";
    }
};
