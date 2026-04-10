#pragma once
// highlight_test_helper.h — C++ equivalent of HighlightTestHelper.swift.
// All functions are inline so this header is the only dependency.

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "driver.h"

// Count non-overlapping occurrences of sub in str.
// Equivalent to Swift's: str.components(separatedBy: sub).count - 1
inline int countOccurrences(const std::string& str, const std::string& sub) {
    int count = 0;
    for (size_t pos = 0; (pos = str.find(sub, pos)) != std::string::npos; pos += sub.size())
        ++count;
    return count;
}

// Split str on '\n'.
// Equivalent to Swift's: str.components(separatedBy: "\n")
inline std::vector<std::string> splitLines(const std::string& str) {
    std::vector<std::string> lines;
    std::istringstream ss(str);
    std::string line;
    while (std::getline(ss, line))
        lines.push_back(line);
    return lines;
}

// Highlight source code using the given language file extension (e.g. "cpp", "py").
inline std::string highlight(const std::string& source, const std::string& langExt) {
    Driver driver;
    return driver.highlight_from_string(source, "snippet." + langExt);
}

// Highlight with engine options (e.g. {"-t"} for tab expansion).
inline std::string highlight(const std::string& source, const std::string& langExt,
                             const std::vector<std::string>& options) {
    Driver driver;
    return driver.highlight_from_string(source, "snippet." + langExt, options);
}

// Find the first line in `lines` that contains `needle`.
// Returns a pointer to the matching line, or nullptr if not found.
// Equivalent to Swift's: lines.first(where: { $0.contains(needle) })
inline const std::string* findLine(const std::vector<std::string>& lines,
                                   const std::string& needle) {
    auto it = std::ranges::find_if(lines, [&](const std::string& l) {
        return l.find(needle) != std::string::npos;
    });
    return it != lines.end() ? &*it : nullptr;
}
