// General department tree with ordered children. Author: OpenAI Codex.
#pragma once
#include "Input.h"

class DepartmentTree {
    struct Node {
        std::string name;
        std::size_t parent, depth;
        std::vector<std::size_t> children;
    };
    std::vector<Node> nodes;
    // Match department names without changing displayed spelling.
    std::size_t find(const std::string& name) const {
        auto wanted = key(name);
        for (std::size_t i = 0; i < nodes.size(); ++i)
            if (key(nodes[i].name) == wanted) return i;
        return nodes.size();
    }
public:
    // Determine whether the next addition creates the root.
    bool empty() const { return nodes.empty(); }
    // Check interactive names before asking for a parent.
    bool contains(const std::string& name) const { return find(name) != nodes.size(); }
    // Insert only after the specified parent has been accepted.
    std::string add(const std::string& name, const std::string& parent) {
        if (trim(name).empty()) return "blank department name";
        if (contains(name)) return "duplicate department";
        if (empty()) {
            if (key(parent) != "NONE") return "first department must use NONE as parent";
            nodes.push_back({trim(name), 0, 0, {}});
        } else {
            auto p = find(parent);
            if (p == nodes.size()) return "unknown parent " + parent;
            auto child = nodes.size();
            nodes.push_back({trim(name), p, nodes[p].depth + 1, {}});
            nodes[p].children.push_back(child);
        }
        return "";
    }
    // Show parent, direct child count, and depth.
    void search(const std::string& name) const {
        if (empty()) { std::cout << "No departments.\n"; return; }
        auto i = find(name);
        if (i == nodes.size()) { std::cout << "Department not found: " << name << '\n'; return; }
        const auto& n = nodes[i];
        std::cout << "Name: " << n.name << "\nParent: " << (i ? nodes[n.parent].name : "None")
                  << "\nChildren: " << n.children.size() << "\nDepth: " << n.depth << '\n';
    }
    // Push children in reverse so the first child is processed first.
    void preorder(bool indent) const {
        if (empty()) { std::cout << "No departments.\n"; return; }
        std::vector<std::size_t> stack{0};
        while (!stack.empty()) {
            const auto& n = nodes[stack.back()];
            stack.pop_back();
            if (indent) std::cout << std::string(4 * n.depth, ' ');
            std::cout << n.name << '\n';
            stack.insert(stack.end(), n.children.rbegin(), n.children.rend());
        }
    }
};
