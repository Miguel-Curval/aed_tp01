#pragma once

#include <string>
#include <ostream>
#include <utility>
#include <vector>

#include "Airport.h"
#include "DateTime.h"

class Flight {
public:
    static unsigned count;
private:
    unsigned seats;
    unsigned number;
    Airport origin;
    Airport destination;
    DateTime departure;
    DateTime arrival;
public:
    Flight() : number(0), origin(), destination(), departure(), arrival(), seats(0) {}

    Flight(Airport origin, Airport destination,
           const DateTime &departure, const DateTime &arrival,
           unsigned seats) : number(count++), origin(std::move(origin)), destination(std::move(destination)),
                             departure(departure), arrival(arrival), seats(seats) {}

    unsigned int getNumber() const {
        return number;
    }

    const Airport &getOrigin() const {
        return origin;
    }

    const Airport &getDestination() const {
        return destination;
    }

    const DateTime &getDeparture() const {
        return departure;
    }

    const DateTime &getArrival() const {
        return arrival;
    }

    const unsigned getSeats() const {
        return seats;
    }

    friend std::ostream &operator<<(std::ostream &os, const Flight &flight) {
        os << flight.number << "\n"
           << flight.origin << flight.destination
           << flight.departure << flight.arrival
           << flight.seats << "\n";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Flight &flight) {
        is >> flight.number
           >> flight.origin >> flight.destination
           >> flight.departure >> flight.arrival
           >> flight.seats;
        return is;
    }


    std::string getStringRep() const {
        return std::to_string(number) + ", " + origin.getStringRep() + ", " + destination.getStringRep() + ", "
        + departure.getStringRep() + ", " + arrival.getStringRep() + ", " + std::to_string(seats);
    }

    static std::vector<std::string> getHeaderElements() {
        return {"Number", "Origin", "Destination", "Departure", "Arrival", "Seats"};
    }

    bool hasSeats() const {
        return seats > 0;
    }

    bool takeSeats(unsigned t) {
        if (seats < t) {
            return false;
        }
        seats -= t;
        return true;
    }

    bool takeSeat() {
        return takeSeats(1);
    }

};
