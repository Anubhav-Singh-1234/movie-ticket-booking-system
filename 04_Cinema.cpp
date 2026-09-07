#pragma once
#include <string>
#include <vector>
#include "03_Screen.cpp"

class Cinema {
private:
    std::string cinemaName;
    // [OOP: Composition - Cinema owns its screens]
    std::vector<Screen> screens;

public:
    Cinema() : cinemaName("PVR Cinemas") {}

    explicit Cinema(const std::string& cinemaName) {
        this->cinemaName = cinemaName;
    }

    void addScreen(const Screen& screen) {
        this->screens.push_back(screen);
    }

    std::string getCinemaName() const { return this->cinemaName; }
    const std::vector<Screen>& getScreens() const { return this->screens; }

    Screen* getScreenByIndex(size_t index) {
        if (index < this->screens.size()) {
            return &(this->screens[index]);
        }
        return nullptr;
    }
};
