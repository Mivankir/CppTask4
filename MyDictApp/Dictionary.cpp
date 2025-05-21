#include "Dictionary.h"
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

void Dictionary::addWord(const wstring& w) {
    if (w.empty()) throw invalid_argument(L"Empty word");
    data_[w]++;
}

void Dictionary::loadFromFile(const wstring& path) {
    wifstream in(path);
    if (!in.is_open()) throw runtime_error(L"Cannot open file: " + path);
    wstring word;
    while (in >> word) addWord(word);
}

void Dictionary::saveToFile(const wstring& path) const {
    wofstream out(path);
    if (!out.is_open()) throw runtime_error(L"Cannot open file: " + path);
    for (auto const& [w, cnt] : data_)
        out << w << L'\t' << cnt << L'\n';
}

vector<pair<wstring, size_t>> Dictionary::getByAlphabet() const {
    vector<pair<wstring, size_t>> v(data_.begin(), data_.end());
    sort(v.begin(), v.end(),
        [](auto const& a, auto const& b) { return a.first < b.first; });
    return v;
}

vector<pair<wstring, size_t>> Dictionary::getByFrequency() const {
    vector<pair<wstring, size_t>> v(data_.begin(), data_.end());
    sort(v.begin(), v.end(),
        [](auto const& a, auto const& b) { return a.second > b.second; });
    return v;
}
