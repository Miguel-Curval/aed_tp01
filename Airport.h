#pragma once

#include <string>
#include <vector>

class Airport {
private:
    std::string name;
public:
    Airport() : name() {}

    Airport(std::string name) : name(std::move(name)) {}

    const std::string &getName() const {
        return name;
    }

    bool operator<(const Airport &rhs) const {
        return name < rhs.name;
    }

    friend std::ostream &operator<<(std::ostream &os, const Airport &airport);

    friend std::istream &operator>>(std::istream &is, Airport &airport);

    std::string getStringRep() const {
        return name;
    }

    static std::vector<std::string> getHeaderElements() {
        return {"Name"};
    }

};
