#!/usr/bin/env bash
# ==============================================================================
# Automated Verification & Test Suite for Movie Ticket Booking System
# ==============================================================================

set -e

APP="./cinema_app"
if [ ! -f "$APP" ]; then
    echo "Building $APP..."
    make build
fi

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}======================================================${NC}"
echo -e "${BLUE}  Running Movie Ticket Booking System Test Suite      ${NC}"
echo -e "${BLUE}======================================================${NC}"

PASS_COUNT=0
TOTAL_TESTS=5

# Test 1: Successful Booking and Ticket Issuance (F1-F7)
echo -n "Test 1: Booking Flow & Ticket Generation (Seats: A1, B2)... "
OUT_T1=$(printf "1\n1\n1\nA1,B2\n1\n0\n" | $APP)
if echo "$OUT_T1" | grep -q "BK1001" && echo "$OUT_T1" | grep -q "CONFIRMED" && echo "$OUT_T1" | grep -q "Rs.400"; then
    echo -e "${GREEN}PASSED${NC}"
    PASS_COUNT=$((PASS_COUNT + 1))
else
    echo -e "${RED}FAILED${NC}"
fi

# Test 2: Double-Booking / Collision Protection
echo -n "Test 2: Collision Rejection for Already Booked Seats (A2)... "
OUT_T2=$(printf "1\n1\n1\nA2\n0\n" | $APP)
if echo "$OUT_T2" | grep -q "Booking rejected: Seat selection conflict"; then
    echo -e "${GREEN}PASSED${NC}"
    PASS_COUNT=$((PASS_COUNT + 1))
else
    echo -e "${RED}FAILED${NC}"
fi

# Test 3: Duplicate Seat Input in Same Request (e.g. 'a3, A3')
echo -n "Test 3: Duplicate Seat Handling ('a3, A3')... "
OUT_T3=$(printf "1\n1\n1\na3, A3\n0\n" | $APP)
if echo "$OUT_T3" | grep -q "Booking rejected"; then
    echo -e "${GREEN}PASSED${NC}"
    PASS_COUNT=$((PASS_COUNT + 1))
else
    echo -e "${RED}FAILED${NC}"
fi

# Test 4: Booking Cancellation & Seat Rollback (F8)
echo -n "Test 4: Booking Cancellation (BK1001 Rollback)... "
OUT_T4=$(printf "1\n1\n1\nA1\n1\n3\nBK1001\n4\n0\n" | $APP)
if echo "$OUT_T4" | grep -q "Booking BK1001 cancelled successfully" && echo "$OUT_T4" | grep -q "CANCELLED"; then
    echo -e "${GREEN}PASSED${NC}"
    PASS_COUNT=$((PASS_COUNT + 1))
else
    echo -e "${RED}FAILED${NC}"
fi

# Test 5: Payment Failure & Seat Release
echo -n "Test 5: Payment Failure Rollback Simulation (Option 4)... "
OUT_T5=$(printf "1\n1\n1\nA3\n4\n0\n" | $APP)
if echo "$OUT_T5" | grep -q "Payment of Rs.150 via fail@bank FAILED" && echo "$OUT_T5" | grep -q "Booking could NOT be confirmed"; then
    echo -e "${GREEN}PASSED${NC}"
    PASS_COUNT=$((PASS_COUNT + 1))
else
    echo -e "${RED}FAILED${NC}"
fi

echo -e "${BLUE}------------------------------------------------------${NC}"
if [ $PASS_COUNT -eq $TOTAL_TESTS ]; then
    echo -e "${GREEN}All $TOTAL_TESTS tests passed successfully!${NC}"
    exit 0
else
    echo -e "${RED}$((TOTAL_TESTS - PASS_COUNT)) test(s) failed.${NC}"
    exit 1
fi
