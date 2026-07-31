#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::size_t> buildLps(const std::string& pattern) {
    std::vector<std::size_t> lps(pattern.size(), 0);
    std::size_t length = 0;
    for (std::size_t i = 1; i < pattern.size();) {
        if (pattern[i] == pattern[length]) {
            lps[i++] = ++length;
        } else if (length > 0) {
            length = lps[length - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

std::size_t kmpFind(const std::string& text, const std::string& pattern) {
    if (pattern.empty()) {
        return 0;
    }
    const auto lps = buildLps(pattern);
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < text.size()) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;
            if (j == pattern.size()) {
                return i - j;
            }
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            ++i;
        }
    }
    return std::string::npos;
}

int main() {
    const std::string text = "ababcabcacbab";
    const std::string pattern = "abcac";
    const auto position = kmpFind(text, pattern);
    std::cout << "匹配位置: " << position << '\n';

    std::cout << "LPS: ";
    for (const auto value : buildLps(pattern)) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}
