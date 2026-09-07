#pragma once
#include <string>

class Movie {
private:
    // [OOP: Encapsulation]
    std::string title;
    std::string language;
    int durationMinutes;

public:
    // [OOP: Compile-Time Polymorphism - Constructor Overloading]
    Movie() : title("Unknown"), language("Unknown"), durationMinutes(0) {}

    Movie(const std::string& title, const std::string& language, int durationMinutes) {
        // [OOP: this Keyword]
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    std::string getTitle() const { return this->title; }
    std::string getLanguage() const { return this->language; }
    int getDurationMinutes() const { return this->durationMinutes; }
};
