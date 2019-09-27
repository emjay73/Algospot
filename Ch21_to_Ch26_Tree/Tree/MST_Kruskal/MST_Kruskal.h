#pragma once

#include "../UnionFind/UnionFind.h"
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_V = 500;

struct MST_Kruskal {
	int V;// number of vertex

	// adjacent list (saves vertex and weight)
	//vector<pair<int, int>> adj[MAX_V];
	vector<pair<int, float>>* adj;
	MST_Kruskal(int _V, vector<pair<int, float>> _adj[])
		:V(_V), adj(_adj)
	{

	}
	// make mst and save it to 'selected'
	// return sum of weight
	// O(|E|log|E|) --> O(|E|) for making tree
	//              --> O(log|E|) for sorting
	float kruskal(vector<pair<int, int>> & selected)
	{
		float ret = 0;
		selected.clear();

		//list of (cost, v1, v2)
		vector < pair<float, pair<int, int>>> edges;

		int v2;
		float v12_weight;
		for (int v1 = 0; v1 < V; ++v1)
		{
			for (int v1_adj = 0; v1_adj < adj[v1].size(); ++v1_adj)
			{
				v2 = adj[v1][v1_adj].first;
				v12_weight = adj[v1][v1_adj].second;
				edges.emplace_back(make_pair(v12_weight, make_pair(v1, v2)));
			}
		}

		// sort based on weight
		sort(edges.begin(), edges.end());

		// at the beginning, every vertex is separated 
		DisjointSet sets(V);

		for (int e = 0; e < edges.size(); ++e)
		{
			auto cost = edges[e].first;
			int v1 = edges[e].second.first;
			int v2 = edges[e].second.second;

			// avoid loop
			if (sets.find_set(v1) == sets.find_set(v2)) continue;
			sets.merge_set(v1, v2);
			selected.emplace_back(make_pair(v1, v2));
			ret += cost;
		}
		return ret;


	}
};
