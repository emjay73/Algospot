#pragma once

// p768
// NaiveDisjointSet
// express disjoint set of n element
// init : n element is its own set
// union : merge two set
// find : given a, return set where a is in

#include <vector>

using namespace std;

typedef struct NaiveDisjointSet {
	vector<int> parent; // of element
	vector<int> rank; // depth (has value only if index equals root)

	NaiveDisjointSet(int n) 
		:parent(n) ,
		 rank(n, 1)
	{
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	// find set of element == root
	int find_set(int idx)
	{
		if (idx == parent[idx]) return idx;
		else return parent[idx]= find_set(parent[idx]);
	}

	// a and b are same set
	// so merge sets (a set--> b set)
	void merge_set(int a, int b)
	{
		// find root of each set
		int ra = find_set(a), rb = find_set(b);

		// already same set
		if (ra == rb) return;
		if (rank[ra] > rank[rb]) swap(ra, rb);
		parent[ra] = rb;

		// only in this case, depth increases by 1
		if (rank[ra] == rank[rb]) ++rank[rb];
	}
} DisjointSet;
