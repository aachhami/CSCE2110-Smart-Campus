// Shared input and load diagnostics. Author: Whole team.
#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Fields = std::vector<std::string>;

// Remove surrounding ASCII whitespace while preserving spaces in names.
inline std::string trim(const std::string& text) {
    const char* spaces = " \t\r\n\f\v";
    auto first = text.find_first_not_of(spaces);
    if (first == std::string::npos) return "";
    return text.substr(first, text.find_last_not_of(spaces) - first + 1);
}

// Produce a case-independent key for names and IDs.
inline std::string key(std::string text) {
    text = trim(text);
    for (char& c : text)
        if (c >= 'a' && c <= 'z') c = char(c - 'a' + 'A');
    return text;
}

// Split a record, retaining empty fields including a trailing one.
inline Fields split(const std::string& line) {
    Fields fields;
    std::size_t start = 0;
    while (true) {
        auto end = line.find('|', start);
        fields.push_back(trim(line.substr(start, end - start)));
        if (end == std::string::npos) return fields;
        start = end + 1;
    }
}

// Validate common syntax and ask the module to accept or reject each record.
// Leave the summary line open so the caller can append hash diagnostics.
template<class Accept>
void load(const std::string& dir, const std::string& file, std::size_t width, Accept accept) {
    std::ifstream input(dir + "/" + file);
    if (!input) std::cout << "Cannot open " << file << '\n';
    std::size_t lineNo = 0, accepted = 0, rejected = 0;
    std::string line;
    while (std::getline(input, line)) {
        ++lineNo;
        line = trim(line);
        if (line.empty() || line.front() == '#') continue;
        auto fields = split(line);
        std::string reason;
        if (fields.size() != width) reason = "wrong field count";
        else if (std::find(fields.begin(), fields.end(), "") != fields.end())
            reason = "empty required field";
        else reason = accept(fields);
        if (reason.empty()) ++accepted;
        else {
            ++rejected;
            std::cout << file << " line " << lineNo << ": " << reason << '\n';
        }
    }
    std::cout << file << ": " << accepted << " accepted, " << rejected << " rejected";
}
