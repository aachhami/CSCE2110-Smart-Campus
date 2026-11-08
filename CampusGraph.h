// Ordered undirected campus graph and BFS. Author: OpenAI Codex.
#pragma once
#include "Input.h"
#include <queue>

class CampusGraph {
    struct Building { std::string name; std::vector<std::size_t> neighbors; };
    std::vector<Building> buildings;
    std::size_t edges = 0;

    // Return the vertex index, or buildings.size() for an unknown name.
    std::size_t index(const std::string& name) const {
        auto wanted = key(name);
        for (std::size_t i = 0; i < buildings.size(); ++i)
            if (key(buildings[i].name) == wanted) return i;
        return buildings.size();
    }
public:
    // Resolve a reference to its accepted spelling.
    std::string canonical(const std::string& name) const {
        auto i = index(name);
        return i == buildings.size() ? "" : buildings[i].name;
    }
    // Append a distinct vertex in file order.
    std::string addBuilding(const Fields& f) {
        if (!canonical(f[0]).empty()) return "duplicate building";
        buildings.push_back({f[0], {}});
        return "";
    }
    // Add both adjacency entries after checking both endpoints.
    std::string connect(const Fields& f) {
        auto a = index(f[0]), b = index(f[1]);
        if (a == buildings.size()) return "unknown building " + f[0];
        if (b == buildings.size()) return "unknown building " + f[1];
        if (a == b) return "self-connection";
        auto& neighbors = buildings[a].neighbors;
        if (std::find(neighbors.begin(), neighbors.end(), b) != neighbors.end())
            return "duplicate connection";
        neighbors.push_back(b);
        buildings[b].neighbors.push_back(a);
        ++edges;
        return "";
    }
    // Display insertion-ordered adjacency lists or degrees.
    void display(bool degrees) const {
        if (degrees) std::cout << "Buildings: " << buildings.size() << "\nConnections: " << edges << '\n';
        if (buildings.empty()) std::cout << "No buildings.\n";
        for (const auto& b : buildings) {
            std::cout << b.name << ": ";
            if (degrees) std::cout << b.neighbors.size();
            else if (b.neighbors.empty()) std::cout << "(no connections)";
            else {
                for (std::size_t j = 0; j < b.neighbors.size(); ++j) {
                    if (j) std::cout << ", ";
                    std::cout << buildings[b.neighbors[j]].name;
                }
            }
            std::cout << '\n';
        }
    }
    // Record distance on enqueue so a vertex enters the queue only once.
    void reachable(const std::string& start) const {
        auto first = index(start);
        if (first == buildings.size()) {
            std::cout << "Unknown building: " << start << '\n';
            return;
        }
        const auto unseen = buildings.size();
        std::vector<std::size_t> distance(buildings.size(), unseen);
        std::queue<std::size_t> pending;
        distance[first] = 0;
        pending.push(first);
        std::size_t count = 0;
        while (!pending.empty()) {
            auto i = pending.front();
            pending.pop();
            ++count;
            std::cout << buildings[i].name << " (distance " << distance[i] << ")\n";
            for (auto j : buildings[i].neighbors) {
                if (distance[j] != unseen) continue;
                distance[j] = distance[i] + 1;
                pending.push(j);
            }
        }
        std::cout << "Reachable: " << count << " of " << buildings.size() << '\n';
    }
};
