#include "LuggageVehicle.h"

bool LuggageVehicle::push(const Luggage & luggage) {
    if (max == total) return false;
    auto i = total / max_per_car;
    cars[i][sizes[i] / max_per_pile].push(luggage);
    return true;
}

Luggage LuggageVehicle::pop() {
    auto i = (total - 1) / max_per_car;
    Pile & pile = cars[i][(sizes[i] - 1) / max_per_pile];
    Luggage luggage = pile.top();
    pile.pop();
    return luggage;
}
