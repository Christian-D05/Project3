#include "enlarger.h"
#include "dsu.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <map>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <chrono>
using namespace std;


vector<pair<int,int>> PrimsAlgorithm(unordered_map<int, vector<pair<int,int>>> targetList) { //exam reviews, Weiss, and Open DSA


  auto begin = chrono::high_resolution_clock::now(); //start the clock
  set<int> nodeSet;
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  vector<pair<int,int>> edges;

  int start = targetList.begin()->first;
  nodeSet.insert(start);

  for (auto neighbor : targetList[start]) {
    pq.push({neighbor.second, neighbor.first});
  }
  while (!pq.empty()) {
    auto [weight, node] = pq.top();
    pq.pop();

    if (nodeSet.count(node)) {
      continue;
    }

    for (auto neighbor : targetList[node]) {
      if (nodeSet.count(neighbor.first)) {
        edges.push_back(make_pair(neighbor.first, node));
        break;
      }
    }
    nodeSet.insert(node);

    for (auto neighbor : targetList[node]) {
      if (!nodeSet.count(neighbor.first)) {
        pq.push({neighbor.second, neighbor.first});
      }
    }

  }

auto end = chrono::high_resolution_clock::now(); //stop the clock
  chrono::duration<double> elapsed = end - begin;
  cout << "Total time Prim's: " << elapsed.count() << " seconds" << endl;

return edges;

}


unordered_map<int, vector<pair<int,int>>> GraphImport(string fileName) { //our data set was unweighted so added random 1-10 weights. can be adjusted

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(1, 10); //makes random 1 through 10
  //int randomNumber = distribution(generator);
  ifstream file(fileName);
  if (!file.is_open()) {
    cout << "Unable to open file " << fileName << endl;
    return unordered_map<int, vector<pair<int,int>>>();
  }
  //cout <<"working";

  unordered_map<int, vector<pair<int,int>>> adjacencyList;
  string line;
  while (getline(file, line)) {
    int u, v;
    stringstream ss(line);
    if (!(ss >> u >> v)) //skips junk in file
      continue;
    int weight = distribution(generator); //makes a random weight
    adjacencyList[u].push_back({v, weight});
    adjacencyList[v].push_back({u, weight});

  }


  //vector<pair<int,int>> mst = PrimsAlgorithm(adjacencyList);
  return adjacencyList;

}


int main() {

    string inputFile = "power-US-Grid.txt";
    string outputFile = "power-US-Grid-100k.txt";

    auto edges = read_edge_list(inputFile);

    cout << "Loaded original graph:" << endl;
    cout << " Original edges: " << edges.size() << endl;

    int times = 21;
    int bridges_per_pair = 20;

    auto enlarged = enlarge_graph(edges, times, bridges_per_pair);

    write_edge_list(outputFile, enlarged);

    cout << "Enlargement Complete" << endl;

    string fileName = "power-US-Grid.rtf"; //rtf file name maybe add entry option but i think necessary

    auto adjacencyList = GraphImport(fileName); //makes graph
    auto result = PrimsAlgorithm(adjacencyList); //runs algorithm and calculates time







  return 0;

}

