// Facility records in file order and indexed lookup. Author: Anup.
#pragma once
#include "CampusGraph.h"
#include "HashTable.h"

class Facilities {
    struct Facility { std::string id, name, building, category; };
    std::vector<Facility> records;
    std::vector<std::string> categories;
    HashTable table;
    // Validate the uppercase ID using ASCII digits.
    static bool valid(const std::string& id) {
        return id.size() == 4 && id[0] == 'F' &&
               id.find_first_not_of("0123456789", 1) == std::string::npos;
    }
    // Print all fields of an accepted record.
    static void print(const Facility& f) {
        std::cout << f.id << " | " << f.name << " | " << f.building << " | " << f.category << '\n';
    }
public:
    // Validate references and ID before recording a category spelling.
    std::string add(const Fields& f, const CampusGraph& graph) {
        auto id = key(f[0]);
        if (!valid(id)) return "invalid ID: expected F plus exactly three digits";
        auto building = graph.canonical(f[2]);
        if (building.empty()) return "unknown building " + f[2];
        if (!table.insert(id, records.size())) return "duplicate ID " + id;
        auto it = std::find_if(categories.begin(), categories.end(),
            [&](const std::string& c) { return key(c) == key(f[3]); });
        if (it == categories.end()) it = categories.insert(it, f[3]);
        records.push_back({id, f[1], building, *it});
        return "";
    }
    // Display all facilities, including the empty case.
    void display() const {
        if (records.empty()) std::cout << "No facilities.\n";
        for (const auto& f : records) print(f);
        std::cout << "Total facilities: " << records.size() << '\n';
    }
    // Distinguish malformed, absent and present keys.
    void search(const std::string& input) const {
        auto id = key(input);
        if (!valid(id)) { std::cout << "Invalid ID: expected F plus exactly three digits.\n"; return; }
        auto i = table.find(id);
        if (i == std::string::npos) std::cout << "Facility not found: " << id << '\n';
        else print(records[i]);
    }
    // Report index statistics after all records are processed.
    void diagnostic() const { table.diagnostic(); }
};
