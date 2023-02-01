#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>

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
    vector<pair<uint64_t, uint32_t> > memref;
    vector<pair<uint64_t, float> > result;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << std::setprecision(1); //Always show 2 decimal places
    cout << std::fixed; //Disable scientific notation for large numbers
    cerr << fixed << showpoint << setprecision(1);
    memref.reserve(400000000);
    result.reserve(400000000);
    ifstream infile;
    infile.open("te");
    string tmp;
    uint64_t memadd;
    int bynum;
    uint64_t instr_n;
    while (infile >> tmp) {
        infile >> dec >> instr_n;
        infile >> tmp >> tmp >> tmp;
        if (tmp[0] == '<') {
            while (tmp.back() != '>') infile >> tmp;
            continue;
        }
        infile >> bynum >> tmp >> tmp >> hex >> memadd >> tmp;
        while (bynum-- > 0) {
            memref.emplace_back(bynum + memadd, instr_n);
        }
        if (tmp == "by") {
            infile >> tmp >> tmp;
            continue;
        }
        if (tmp == "conditional" || tmp == "indirect") {
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
    cout << setw(6) << "address" << setw(5) << "reuse distance\n";
    for (auto i: result) {
        cout << setw(30) << i.first << "  " << setw(5) << i.second << "\n";
    }
    return 0;
}
