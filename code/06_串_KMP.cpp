#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* 作用：计算模式串的 LPS 数组。pattern 是模式串，返回每个位置的最长相等前后缀长度。 */
vector<int> buildLps(const string& pattern) {
    vector<int> lps(pattern.size(), 0);
    int length = 0; // 当前已经找到的相等前后缀长度
    int i = 1;      // 正在计算 lps[i]
    while (i < (int)pattern.size()) {
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

/* 作用：在 text 中查找 pattern。找到返回起始下标，找不到返回 -1。 */
int kmpFind(const string& text, const string& pattern) {
    if (pattern.empty()) {
        return 0;
    }
    vector<int> lps = buildLps(pattern);
    int i = 0; // 主串下标，只向右移动
    int j = 0; // 模式串下标，失配时按 lps 回退
    while (i < (int)text.size()) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;
            if (j == (int)pattern.size()) {
                return i - j;
            }
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            ++i;
        }
    }
    return -1;
}

int main() {
    string text = "ababcabcacbab";
    string pattern = "abcac";
    int position = kmpFind(text, pattern);
    cout << "匹配位置: " << position << '\n';

    cout << "LPS: ";
    vector<int> lps = buildLps(pattern);
    for (int i = 0; i < (int)lps.size(); i++) {
        cout << lps[i] << ' ';
    }
    cout << '\n';
    return 0;
}
