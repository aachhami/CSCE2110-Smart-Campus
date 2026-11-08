// Facility ID index with separate chaining. Author: OpenAI Codex.
#pragma once
#include "Input.h"

class HashTable {
    struct Entry { std::string id; std::size_t record; };
    static constexpr std::size_t capacity = 17;
    std::vector<std::vector<Entry>> buckets{capacity};
    std::size_t entries = 0, collisions = 0;

    // Hash an already normalized ID into a bucket.
    std::size_t bucket(const std::string& normalized) const {
        std::size_t h = 0;
        for (unsigned char c : normalized) h = (31 * h + c) % capacity;
        return h;
    }
public:
    // Return the matching record index or npos after inspecting only its chain.
    std::size_t find(const std::string& id) const {
        auto normalized = key(id);
        for (const auto& entry : buckets[bucket(normalized)])
            if (entry.id == normalized) return entry.record;
        return std::string::npos;
    }
    // Reject duplicate keys; count only accepted insertions into nonempty chains.
    bool insert(const std::string& id, std::size_t record) {
        auto normalized = key(id);
        if (find(normalized) != std::string::npos) return false;
        auto& chain = buckets[bucket(normalized)];
        if (!chain.empty()) ++collisions;
        chain.push_back({normalized, record});
        ++entries;
        return true;
    }
    // Complete the facility load summary.
    void diagnostic() const {
        std::cout << " (capacity " << capacity << ", entries " << entries
                  << ", collisions " << collisions << ")\n";
    }
};
