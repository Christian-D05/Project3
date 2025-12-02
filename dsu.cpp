#include "dsu.h"

DSU::DSU(int n) {
	parent.resize(n);
	rank.assign(n, 0);
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
}

int DSU::find(int x) {
	if (parent[x] != x) {
		parent[x] = find(parent[x]);
	}
	return parent[x];
}

void DSU::unite(int x, int y) {
	x = find(x);
	y = find(y);

	if (x == y) return;

	if (rank[x] < rank[y]) {
		parent[x] = y;
	}
	else if (rank[x] > rank[y]) {
		parent[y] = x;
	}
	else {
		parent[y] = x;
		rank[x]++;
	}
}