#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "06_ShowSeat.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

static std::vector<std::string> parseSeatList(const std::string& input) {
    std::vector<std::string> seatTokens;
    std::stringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ',')) {
        std::string cleaned = trim(token);
        if (!cleaned.empty()) {
            for (char& c : cleaned) {
                c = static_cast<char>(std::toupper(c));
            }
            seatTokens.push_back(cleaned);
        }
    }
    return seatTokens;
}

static Screen createStandardScreen(const std::string& name) {
    Screen screen(name);
    screen.addSeat(Seat("A1", SeatType::SILVER));
    screen.addSeat(Seat("A2", SeatType::SILVER));
    screen.addSeat(Seat("A3", SeatType::SILVER));
    screen.addSeat(Seat("A4", SeatType::SILVER));

    screen.addSeat(Seat("B1", SeatType::GOLD));
    screen.addSeat(Seat("B2", SeatType::GOLD));
    screen.addSeat(Seat("B3", SeatType::GOLD));

    screen.addSeat(Seat("C1", SeatType::PLATINUM));
    screen.addSeat(Seat("C2", SeatType::PLATINUM));
    return screen;
}

static void listAllMovies(const std::vector<Movie>& movies) {
    std::cout << "\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " 
                  << std::left << std::setw(15) << movies[i].getTitle()
                  << std::setw(10) << movies[i].getLanguage()
                  << movies[i].getDurationMinutes() << " min\n";
    }
}

// Feature 2: List shows for a chosen movie
static std::vector<Show*> getShowsForMovie(const Movie& movie, std::vector<Show>& allShows) {
    std::vector<Show*> movieShows;
    for (Show& show : allShows) {
        if (show.getMovie()->getTitle() == movie.getTitle()) {
            movieShows.push_back(&show);
        }
    }
    return movieShows;
}

static void displayShowsList(const std::vector<Show*>& shows) {
    for (size_t i = 0; i < shows.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " 
                  << std::left << std::setw(10) << shows[i]->getScreen()->getScreenName()
                  << shows[i]->getStartTime() << "\n";
    }
}

static std::unique_ptr<Payment> selectPaymentMethod(bool allowFailureSimulation = true) {
    std::cout << "\nPay by: 1.UPI  2.Card  3.Cash > ";
    int paymentChoice = 0;
    if (!(std::cin >> paymentChoice)) {
        if (std::cin.eof()) return nullptr;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return nullptr;
    }

    if (paymentChoice == 1) {
        return std::make_unique<UpiPayment>("anubhav@okaxis", true);
    } else if (paymentChoice == 2) {
        return std::make_unique<CardPayment>("5241-XXXX-XXXX-9901", true);
    } else if (paymentChoice == 3) {
        return std::make_unique<CashPayment>(true);
    } else if (paymentChoice == 4 && allowFailureSimulation) {
        return std::make_unique<UpiPayment>("fail@bank", false);
    }
    return nullptr;
}

static void displaySeatPriceBreakdown(const std::vector<ShowSeat*>& selectedSeats) {
    double totalAmount = 0.0;
    for (const ShowSeat* seat : selectedSeats) {
        std::cout << "  " << std::left << std::setw(3) << seat->getSeatNumber() 
                  << std::setw(7) << seat->getSeatTypeString() 
                  << "Rs." << static_cast<int>(seat->getPrice()) << "\n";
        totalAmount += seat->getPrice();
    }
    std::cout << "  TOTAL     Rs." << static_cast<int>(totalAmount) << "\n";
}

static void handleBookingFlow(Show& chosenShow, Customer& customer, BookingService& bookingService) {
    chosenShow.displaySeatLayout();

    std::cout << "\nSeats (e.g. A1,B2): ";
    std::string seatInput;
    if (!(std::cin >> std::ws) || !std::getline(std::cin, seatInput)) {
        return;
    }

    std::vector<std::string> seatNumbers = parseSeatList(seatInput);
    if (seatNumbers.empty()) {
        std::cout << "Invalid seat selection. Operation aborted.\n";
        return;
    }

    std::vector<ShowSeat*> selectedSeats = bookingService.validateAndSelectSeats(chosenShow, seatNumbers);
    if (selectedSeats.size() != seatNumbers.size()) {
        std::cout << "Booking rejected: Seat selection conflict or invalid seat ID.\n";
        return;
    }

    displaySeatPriceBreakdown(selectedSeats);

    auto paymentMethod = selectPaymentMethod(true);
    if (!paymentMethod) {
        std::cout << "Invalid payment choice. Booking aborted.\n";
        return;
    }

    bookingService.processBooking(customer, chosenShow, selectedSeats, *paymentMethod);
}

static void handleMovieSelection(const std::vector<Movie>& movies, std::vector<Show>& shows,
                                 Customer& customer, BookingService& bookingService) {
    listAllMovies(movies);
    std::cout << "\nChoose movie: ";
    size_t movieChoice = 0;
    if (!(std::cin >> movieChoice) || movieChoice < 1 || movieChoice > movies.size()) {
        if (std::cin.eof()) return;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid movie choice.\n";
        return;
    }

    const Movie& chosenMovie = movies[movieChoice - 1];
    std::vector<Show*> availableShows = getShowsForMovie(chosenMovie, shows);
    if (availableShows.empty()) {
        std::cout << "No shows available for this movie.\n";
        return;
    }

    displayShowsList(availableShows);
    std::cout << "Choose show: ";
    size_t showChoice = 0;
    if (!(std::cin >> showChoice) || showChoice < 1 || showChoice > availableShows.size()) {
        if (std::cin.eof()) return;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid show choice.\n";
        return;
    }

    Show* selectedShow = availableShows[showChoice - 1];
    handleBookingFlow(*selectedShow, customer, bookingService);
}

int main() {
    Cinema cinema("PVR Cinemas - Grand Mall");
    Screen screen1 = createStandardScreen("Screen-1");
    Screen screen2 = createStandardScreen("Screen-2");
    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    Screen* pScreen1 = cinema.getScreenByIndex(0);
    Screen* pScreen2 = cinema.getScreenByIndex(1);

    std::vector<Movie> movies = {
        Movie("3 Idiots", "Hindi", 170),
        Movie("Interstellar", "English", 169)
    };

    std::vector<Show> shows = {
        Show(1, &movies[0], pScreen1, "06:00 PM"),
        Show(2, &movies[0], pScreen2, "09:00 PM"),
        Show(3, &movies[1], pScreen1, "09:00 PM")
    };

    ShowSeat* preA2 = shows[0].findShowSeat("A2");
    if (preA2) preA2->bookSeat();
    ShowSeat* preB3 = shows[0].findShowSeat("B3");
    if (preB3) preB3->bookSeat();

    Customer currentCustomer("Anubhav Panwar", "9876543210");
    BookingService bookingService;

    std::cout << "===== MOVIE TICKET BOOKING =====\n";

    while (true) {
        std::cout << "\n1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit\n";
        std::cout << "Choose: ";

        int mainChoice = -1;
        if (!(std::cin >> mainChoice)) {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a valid menu number.\n";
            continue;
        }

        if (mainChoice == 0) {
            std::cout << "Thank you for using PVR Cinema Booking System. Goodbye!\n";
            break;
        }

        if (mainChoice == 1 || mainChoice == 2) {
            handleMovieSelection(movies, shows, currentCustomer, bookingService);
        } else if (mainChoice == 3) {
            std::cout << "\nEnter Booking ID to cancel (e.g. BK1001): ";
            std::string bookingId;
            if (std::cin >> bookingId) {
                bookingService.cancelBookingById(bookingId);
            }
        } else if (mainChoice == 4) {
            const auto& allBookings = bookingService.getAllBookings();
            if (allBookings.empty()) {
                std::cout << "No bookings recorded yet.\n";
            } else {
                for (const auto& b : allBookings) {
                    bookingService.printBookingTicket(b);
                }
            }
        } else {
            std::cout << "Invalid choice! Please select an option between 0 and 4.\n";
        }
    }

    return 0;
}
