#pragma once

#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<int, int>> read_edge_list(const std::string& filename);
std::vector<std::pair<int, int>> enlarge_graph(const std::vector<std::pair<int, int>>& edges, int times, int bridges_per_pair);

void write_edge_list(const std::string& filename, const std::vector<std::pair<int, int>>& edges);
