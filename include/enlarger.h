#pragma once

#include <vector>
#include <string>
#include <utility>

using namespace std;

vector<pair<int, int>> read_edge_list(const string& filename);
vector<pair<int, int>> enlarge_graph(const vector<pair<int, int>>& edges, int times, int bridges_per_pair);

void write_edge_list(const string& filename, const vector<pair<int, int>>& edges);
