#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;
 
class Dictionary {
public:
    void addWord(const wstring& w);
    void loadFromFile(const wstring& path);
    void saveToFile(const wstring& path) const;
    vector<pair<wstring, size_t>> getByAlphabet() const;
    vector<pair<wstring, size_t>> getByFrequency() const;

private:
    map<wstring, size_t> data_;
};
