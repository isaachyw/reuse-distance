#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class EqualCmp {
public:

    explicit EqualCmp(uint64_t _val) : val(_val) {}

    bool operator()(const pair<uint64_t, uint32_t> &ele) const {
        return ele.first == val;
    }

private:
    uint64_t val;
};


std::vector<size_t> findItems(std::vector<pair<uint64_t, uint32_t>> const &v, uint64_t target) {
    std::vector<size_t> indices;
    auto it = v.begin();
    while ((it = std::find_if(it, v.end(), [&](pair<uint64_t, uint32_t> const &e) { return e.first == target; }))
           != v.end()) {
        indices.push_back(std::distance(v.begin(), it));
        it++;
    }
    return indices;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<uint64_t, uint32_t> > memref;
    vector<pair<uint64_t, float> > result;
    memref.reserve(20000000);
    result.reserve(20000000);
    ifstream infile;
    infile.open("te.txt");
    string tmp;
    uint64_t memadd;
    uint8_t bynum;
    uint32_t instr_n;
    while (infile >> tmp) {
        infile >> instr_n >> tmp >> tmp >> tmp >> bynum >> tmp >> tmp >> hex >> memadd >> tmp;
        while (bynum-- > 0) {
            memref.emplace_back(bynum + memadd, instr_n);
        }
        if (tmp[0] == 'b') {
            infile >> tmp >> tmp;
            continue;
        }
        if (tmp[0] == 'c') {
            infile >> tmp;
            continue;
        }
    }
    while (!memref.empty()) {
        auto first = memref[0];
        vector<size_t> tmpidc = findItems(memref, first.first);
        if (tmpidc.size() > 1) {
            float avg = (memref[tmpidc.back()].second - memref[tmpidc.front()].second - (tmpidc.size() - 1)) /
                        (tmpidc.size() - 1);
            result.emplace_back(first.first, avg);
        }
        auto newend = remove_if(memref.begin(), memref.end(), EqualCmp(memref[0].first));
        memref.erase(newend, memref.end());
    }
    cout << "end";
    return 0;
}
