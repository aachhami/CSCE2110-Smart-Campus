// Team menu adapted from the repository starter. Integration author: OpenAI Codex.
#include "DepartmentTree.h"
#include "Facilities.h"
#include <sstream>

// Display the team's numbered Milestone 1 menu.
void showMenu() {
    std::cout << "1. View all facilities" << '\n';
    std::cout << "2. Search facility by ID" << '\n';
    std::cout << "3. View campus graph" << '\n';
    std::cout << "4. Display graph counts and degrees" << '\n';
    std::cout << "5. Find reachable buildings (BFS)" << '\n';
    std::cout << "6. Add department" << '\n';
    std::cout << "7. Search department" << '\n';
    std::cout << "8. Display department hierarchy" << '\n';
    std::cout << "9. Run preorder traversal" << '\n';
    std::cout << "10. Exit" << '\n' << '\n';
    std::cout << "Enter your choice: ";
}

// Read a full name and report blanks before returning to the menu.
bool readName(const std::string& prompt, std::string& value) {
    std::cout << prompt << '\n';
    if (!std::getline(std::cin, value)) return false;
    value = trim(value);
    if (!value.empty()) return true;
    std::cout << "Name cannot be blank.\n";
    return false;
}

// Initialize the shared structures and dispatch menu operations.
int main(int argc, char** argv) {
    std::string dir = argc > 1 ? argv[1] : "data";
    CampusGraph graph;
    Facilities facilities;
    DepartmentTree tree;
    load(dir, "buildings.txt", 1, [&](const Fields& f) { return graph.addBuilding(f); });
    std::cout << '\n';
    load(dir, "connections.txt", 2, [&](const Fields& f) { return graph.connect(f); });
    std::cout << '\n';
    load(dir, "facilities.txt", 4, [&](const Fields& f) { return facilities.add(f, graph); });
    facilities.diagnostic();
    load(dir, "departments.txt", 2, [&](const Fields& f) { return tree.add(f[0], f[1]); });
    std::cout << '\n';

    std::string line, name, parent;
    while (std::cin) {
        showMenu();
        if (!std::getline(std::cin, line)) break;
        std::istringstream input(line);
        int choice;
        char extra;
        if (!(input >> choice) || (input >> extra) || choice < 0 || choice > 10) {
            std::cout << "Invalid menu choice.\n";
            continue;
        }
        switch (choice) {
        case 0:
        case 10: std::cout << "Exiting program...\n"; return 0;
        case 1: facilities.display(); break;
        case 2:
            std::cout << "Facility ID?\n";
            if (std::getline(std::cin, line)) facilities.search(line);
            break;
        case 3: graph.display(false); break;
        case 4: graph.display(true); break;
        case 5:
            if (readName("Starting building?", name)) graph.reachable(name);
            break;
        case 6: {
            if (!readName("New department?", name)) break;
            if (tree.contains(name)) { std::cout << "duplicate department\n"; break; }
            parent = "NONE";
            if (!tree.empty() && !readName("Parent department?", parent)) break;
            auto reason = tree.add(name, parent);
            std::cout << (reason.empty() ? "Department added." : reason) << '\n';
            break;
        }
        case 7:
            if (readName("Department name?", name)) tree.search(name);
            break;
        case 8: tree.preorder(true); break;
        case 9: tree.preorder(false); break;
        }
    }
}
