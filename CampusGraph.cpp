// CampusGraph.cpp
// Purpose: Load and validate campus building records.

#include <algorithm>
#include "CampusGraph.h"

#include <fstream>
#include <iostream>

namespace {

// Remove surrounding whitespace, including carriage returns from Windows files.
std::string trim(const std::string& text) {
    const std::string whitespace = " \t\r\n\f\v";
    const auto first = text.find_first_not_of(whitespace);

    if (first == std::string::npos) {
        return "";
    }

    const auto last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

// Make a comparison key while preserving the original name for display.
std::string nameKey(std::string name) {
    for (char& letter : name) {
        if (letter >= 'a' && letter <= 'z') {
            letter = static_cast<char>(letter - 'a' + 'A');
        }
    }
    return name;
}

} // namespace

// Read buildings in file order and report accepted and rejected records.
void CampusGraph::loadBuildings(const std::string& dataDirectory) {
    buildings.clear();

    std::ifstream file(dataDirectory + "/buildings.txt");
    if (!file) {
        std::cout << "Error: cannot open buildings.txt\n";
        std::cout << "buildings.txt: 0 accepted, 0 rejected\n";
        return;
    }

    std::string line;
    std::size_t lineNumber = 0;
    std::size_t rejected = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        const std::string name = trim(line);

        if (name.empty() || name.front() == '#') {
            continue;
        }

        if (name.find('|') != std::string::npos) {
            std::cout << "Warning: buildings.txt line " << lineNumber
                      << ": expected one building name\n";
            ++rejected;
            continue;
        }

        const std::string wanted = nameKey(name);
        bool duplicate = false;

        for (const Building& building : buildings) {
            if (nameKey(building.name) == wanted) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            std::cout << "Warning: buildings.txt line " << lineNumber
                      << ": duplicate building " << name << '\n';
            ++rejected;
            continue;
        }

        buildings.push_back({name, {}});
    }

    std::cout << "buildings.txt: " << buildings.size()
              << " accepted, " << rejected << " rejected\n";
}

// Find a building by name, ignoring capitalization and outer whitespace.
std::size_t CampusGraph::findBuilding(const std::string& name) const {
    const std::string wanted = nameKey(trim(name));

    for (std::size_t i = 0; i < buildings.size(); ++i) {
        if (nameKey(buildings[i].name) == wanted) {
            return i;
        }
    }

    return buildings.size();
}

// Load each valid walkway once and connect its two endpoints.
void CampusGraph::loadConnections(const std::string& dataDirectory) {
    for (Building& building : buildings) {
        building.neighbors.clear();
    }

    std::ifstream file(dataDirectory + "/connections.txt");
    if (!file) {
        std::cout << "Error: cannot open connections.txt\n";
        std::cout << "connections.txt: 0 accepted, 0 rejected\n";
        return;
    }

    std::string line;
    std::size_t lineNumber = 0;
    std::size_t accepted = 0;
    std::size_t rejected = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        line = trim(line);

        if (line.empty() || line.front() == '#') {
            continue;
        }

        std::string reason;
        const auto separator = line.find('|');

        if (separator == std::string::npos ||
            line.find('|', separator + 1) != std::string::npos) {
            reason = "expected two building names separated by |";
        } else {
            const std::string first = trim(line.substr(0, separator));
            const std::string second = trim(line.substr(separator + 1));
            const auto a = findBuilding(first);
            const auto b = findBuilding(second);

            if (first.empty() || second.empty()) {
                reason = "empty building name";
            } else if (a == buildings.size()) {
                reason = "unknown building " + first;
            } else if (b == buildings.size()) {
                reason = "unknown building " + second;
            } else if (a == b) {
                reason = "self-connection";
            } else {
                auto& neighbors = buildings[a].neighbors;

                if (std::find(neighbors.begin(), neighbors.end(), b)
                    != neighbors.end()) {
                    reason = "duplicate connection";
                } else {
                    neighbors.push_back(b);
                    buildings[b].neighbors.push_back(a);
                    ++accepted;
                }
            }
        }

        if (!reason.empty()) {
            ++rejected;
            std::cout << "Warning: connections.txt line " << lineNumber
                      << ": " << reason << '\n';
        }
    }

    std::cout << "connections.txt: " << accepted
              << " accepted, " << rejected << " rejected\n";
}