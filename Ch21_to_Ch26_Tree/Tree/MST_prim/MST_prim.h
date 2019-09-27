#pragma once

#include <vector>
using namespace std;
const int MAX_V = 1000;
const float INF = 987654321.0f;


struct MST_Prim
{

	// number of node
	int V;

	//graph adjacent list
	// adj[v1] = (v2, weight)
	//vector<pair<int, int>> adj[MAX_V];
	vector<pair<int, float>> *adj;

	MST_Prim(int _V, vector<pair<int, float>>_adj[])
		: V(_V),adj(_adj)

	{

	}
	// make mst = 'selected'
	// return sum of weights
	float prim(vector < pair<int, int>> & selected)
	{
		selected.clear();

		// v is in selected?
		vector<bool> in_selected(V, false);

		// find adjacent min weight of mst
		vector<float> min_weight(V, INF), parent(V, -1);

		// sum of weights
		float ret = 0;

		// v=0 is starting point
		min_weight[0] = 0.0f;
		parent[0] = 0;
		// in_selected[0] = true; //will be done inside for loop

		for (int iter = 0; iter < V; ++iter)
		{
			int next_node = -1;
			for (int v = 0; v < V; ++v)
			{
				if (!in_selected[v] &&
					(next_node == -1 || min_weight[next_node] > min_weight[v]))
					next_node = v;
			}

			if (parent[next_node] != next_node)
				selected.emplace_back(make_pair(parent[next_node], next_node));

			ret += min_weight[next_node];
			in_selected[next_node] = true;

			//check next_node's adjacents
			for (int iv = 0; iv < adj[next_node].size(); ++iv)
			{
				int v = adj[next_node][iv].first;	// vertex
				auto w = adj[next_node][iv].second;  // weight
				if (!in_selected[v] && min_weight[v] > w) {
					parent[v] = next_node;
					min_weight[v] = w;
				}
			}
		}
		return ret;
	}
};

