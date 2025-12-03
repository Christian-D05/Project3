#include "enlarger.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

using namespace std;

vector<pair<int, int>> read_edge_list(const string& filename) {
    ifstream file(filename);
    vector<pair<int, int>> edges;

    if (!file.is_open()) {
        cout << "ERROR: Unable to open file " << filename << endl;
        return edges;
    }

    string line;
    while (getline(file, line)) {
        int u, v;
        stringstream ss(line);
        if (!(ss >> u >> v)) continue;
        if (u < 1 || v < 1) continue;
        edges.emplace_back(u, v);
    }

    return edges;
}

vector<pair<int, int>> enlarge_graph(const vector<pair<int, int>>& edges, int times, int bridges_per_pair) {
    if (times < 1) return edges;

    int max_node = 0;
    for (const auto& e : edges) {
        max_node = max(max_node, max(e.first, e.second));
    }

    vector<pair<int, int>> big;
    big.reserve(edges.size() * times + bridges_per_pair * (times - 1));

    for (int t = 0; t < times; t++) {
        int offset = t * (max_node + 1);

        for (const auto& e : edges) {
            big.emplace_back(e.first + offset, e.second + offset);
        }
    }

    random_device rd;
    mt19937 gen(rd());

    for (int t = 0; t < times - 1; t++) {
        int offsetA = t * (max_node + 1);
        int offsetB = (t + 1) * (max_node + 1);

        uniform_int_distribution<int> dist(1, max_node);

        for (int b = 0; b < bridges_per_pair; b++) {
            int a = dist(gen) + offsetA;
            int c = dist(gen) + offsetB;
            big.emplace_back(a, c);
        }
    }

    return big;
}

void write_edge_list(const string& filename, const vector<pair<int, int>>& edges) {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "ERROR: Unable to write file " << filename << endl;
        return;
    }

    for (const auto& e : edges) {
        out << e.first << " " << e.second << "\n";
    }

    out.close();
}