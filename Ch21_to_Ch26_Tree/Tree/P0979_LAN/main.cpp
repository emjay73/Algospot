
#include "../MST_prim/MST_prim.h"
//#include "../MST_Kruskal/MST_Kruskal.h"
#include <iostream>
#include <iomanip>
using namespace std;

int N, M;
vector<pair<int, float>> adj[MAX_V];
vector<float> xs;
vector<float> ys;
vector<vector<float>> dist;
vector<pair<int, int>> already;
int main()
{
	int C;

	cin >> C;

	while (C--)
	{
		cin >> N >> M;
		xs.resize(N);
		ys.resize(N);
		//dist.resize(N);
		already.resize(M);
		for (int n = 0; n < N; ++n)
			cin >> xs[n];
		for (int n = 0; n < N; ++n)
			cin >> ys[n];

		for (int v1 = 0; v1 < N; ++v1)
		{
			//dist[v1].resize(N);

			for (int v2 = 0; v2 < N; ++v2)
			{
				if (v1 == v2) continue;
				float weight = sqrtf(	(xs[v1] - xs[v2])*(xs[v1] - xs[v2]) +
									(ys[v1] - ys[v2])*(ys[v1] - ys[v2]));
				adj[v1].emplace_back(make_pair(v2, weight));
				/*dist[v1][v2] = sqrt((xs[v1] - xs[v2])*(xs[v1] - xs[v2]) +
									(ys[v1] - ys[v2])*(ys[v1] - ys[v2]));*/
			}
		}
		
		for (int m = 0; m < M; ++m)
		{
			cin >> already[m].first >> already[m].second;

			for (int iv = 0; iv < adj[already[m].first].size(); ++iv)
			{
				int v1 = adj[already[m].first][iv].first;
				int v2 = adj[already[m].second][iv].first;

				if (v1 == already[m].second) 
					adj[already[m].first][iv].second = 0.0f;

				if (v2 == already[m].first)
					adj[already[m].second][iv].second = 0.0f;
			}
			
				
		}
			
		vector<pair<int, int>> selected;

		MST_Prim mst_prim(N, adj);		
		cout << setprecision(11)<< mst_prim.prim(selected) << endl;

		/*MST_Kruskal mstk(N, adj);
		cout << setprecision(11) << mstk.kruskal(selected) << endl;*/


	}

}