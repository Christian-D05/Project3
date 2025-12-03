#pragma once

#include "dsu.h"
#include <vector>
#include <utility>
#include <string>

struct Edge {
	int u, v, w;
};

std::vector<Edge> create_weighted_edges(const std::vector<pair<int, int>>& raw_edges);

long long kruskal_mst(std::vector <Edge>& edges, int num_nodes);
