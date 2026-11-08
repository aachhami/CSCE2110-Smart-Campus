// Main.cpp
// Purpose: Display the Milestone 1 menu and handle the user's selection.
// Original menu: CSCE 2110 Smart Campus project team.

#include "CampusGraph.h"
#include <iostream>
#include <sstream>
#include <string>

// Display the available Milestone 1 operations.
void displayMenu() {
    std::cout << "\nSmart Campus Navigation and Facility Analytics\n"
              << "1. View all facilities\n"
              << "2. Search facility by ID\n"
              << "3. View campus graph\n"
              << "4. Display graph counts and degrees\n"
              << "5. Find reachable buildings (BFS)\n"
              << "6. Add department\n"
              << "7. Search department\n"
              << "8. Display department hierarchy\n"
              << "9. Run preorder traversal\n"
              << "10. Exit\n\n"
              << "Enter your choice: ";
}

// Accept one whole number with optional surrounding whitespace.
// Section 6.9 lists 10 as Exit, and requirement UI-7 also allows 0.
bool parseMenuChoice(const std::string& line, int& choice) {
    std::istringstream input(line);
    char extra;

    if (!(input >> choice)) {
        return false;
    }

    if (input >> extra) {
        return false;
    }

    return choice >= 0 && choice <= 10;
}

// Repeat the menu until the user selects Exit or closes the input.
int main(int argc, char* argv[]) {
    const std::string dataDirectory = (argc > 1) ? argv[1] : "data";

    CampusGraph graph;
    graph.loadBuildings(dataDirectory);
	graph.loadConnections(dataDirectory);

    std::string line;

    while (true) {
        displayMenu();

        if (!std::getline(std::cin, line)) {
            break;
        }

        int choice;
        if (!parseMenuChoice(line, choice)) {
            std::cout << "Invalid choice. Enter a number from 1 to 10.\n";
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "Viewing all facilities...\n";
                break;

            case 2:
                std::cout << "Searching facility by ID...\n";
                break;

            case 3:
                std::cout << "Viewing campus graph...\n";
                break;

            case 4:
                std::cout << "Displaying graph counts and degrees...\n";
                break;

            case 5:
                std::cout << "Finding reachable buildings (BFS)...\n";
                break;

            case 6:
                std::cout << "Adding department...\n";
                break;

            case 7:
                std::cout << "Searching department...\n";
                break;

            case 8:
                std::cout << "Displaying department hierarchy...\n";
                break;

            case 9:
                std::cout << "Running preorder traversal...\n";
                break;

            case 0:
            case 10:
                std::cout << "Exiting program...\n";
                return 0;
        }
    }

    return 0;
}