#pragma once

#include <stack>
#include <string>
#include <vector>

#include "Luggage.h"

using Pile = std::stack<Luggage>;

using Car = std::vector<Pile>;

class LuggageVehicle {
private:
    unsigned total;
    std::vector<unsigned> sizes;
    const unsigned max;
    const unsigned max_per_car;
    const unsigned max_per_pile;
    std::vector<Car> cars;
    std::string str_body;
    std::string str_base;
    std::string str_wheels;
public:
    LuggageVehicle(unsigned num_cars,
                   unsigned num_piles_per_car,
                   unsigned max_per_pile) : total(0), sizes(num_cars, 0),
                                            max(num_cars * num_piles_per_car * max_per_pile),
                                            max_per_car(num_piles_per_car * max_per_pile),
                                            max_per_pile(max_per_pile),
                                            cars(num_cars, Car(num_piles_per_car)) {
        str_body = std::string(num_piles_per_car, ' ');
        str_base = std::string(num_piles_per_car, '#');
        str_body = "|" + str_body + "|";
        str_base = "|" + str_base + "|";
    }


    unsigned size() const {
        return total;
    }

    bool empty() const {
        return total == 0;
    }

    bool push(const Luggage & luggage);

    Luggage pop();

    std::string getStringRep() {
        return str_body + "\n" + str_base;
    }

};
