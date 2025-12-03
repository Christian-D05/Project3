#include "kruskal.h"
#include <algorithm>
#include <random>

using namespace std;

vector<Edge> create_weighted_edges(const vector<pair<int, int>>& raw_edges) {
	vector<Edge> edges;
	edges.reserve(raw_edges.size());
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, 100);

	for (auto& p : raw_edges) {
		edges.push_back({ p.first, p.second, dist(gen) });
	}

	return edges;
}

long long kruskal_mst(vector<Edge>& edges, int num_nodes) {
	sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
		return a.w < b.w;
	});
		
	DSU dsu(num_nodes);
	
	long long total_weight = 0;
	int edges_used = 0;
	
	for (auto& e : edges) {
		if (dsu.find(e.u) != dsu.find(e.v)) {
			dsu.unite(e.u, e.v);
			total_weight += e.w;
			edges_used++;

			if (edges_used == num_nodes - 1) {
				break;
			}
		}
	}
	return total_weight;
}