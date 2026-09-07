# ==============================================================================
# Movie Ticket Booking System - Makefile
# Object-Oriented C++17 Cinema Management Platform
# ==============================================================================

CXX      ?= clang++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -O2
TARGET   = cinema_app
SRCS     = main.cpp

.PHONY: all build run test clean help

all: build

build: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
	@echo "Build successful: ./$(TARGET)"

run: build
	./$(TARGET)

test: build
	@chmod +x test_demo.sh
	./test_demo.sh

clean:
	rm -rf $(TARGET) *.dSYM *.o
	@echo "Cleaned build artifacts."

help:
	@echo "Usage:"
	@echo "  make        - Build the $(TARGET) binary"
	@echo "  make run    - Build and launch the interactive cinema CLI"
	@echo "  make test   - Run automated test cases and edge-case validations"
	@echo "  make clean  - Remove compiled binaries and debug symbols"
	@echo "  make help   - Display this help message"
