// CampusGraph.h
// Author: Anup Achhami
// Purpose: Store campus buildings and their walkway connections.

#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

#include <cstddef>
#include <string>
#include <vector>

class CampusGraph {
public:
    // Load buildings from buildings.txt in the selected data directory.
    void loadBuildings(const std::string& dataDirectory);
    // Load undirected walkways between accepted buildings.
void loadConnections(const std::string& dataDirectory);

private:
    struct Building {
        std::string name;
        std::vector<std::size_t> neighbors;
    };

    std::vector<Building> buildings;
    // Return the building's index, or buildings.size() if it is unknown.
std::size_t findBuilding(const std::string& name) const;
};

#endif