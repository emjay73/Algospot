#include "../RMQ_range_minimum_query/RMQ.h"
#include <iostream>
#include <vector>

using namespace std;
int main()
{
	int C;
	int N; // number of signs
	int Q; // number of new roads
	

	vector<int> h, h_neg;
	vector<vector<int>> q;
	cin >> C;
	while (C--)
	{
		cin >> N >> Q;
		
		h.clear();	h_neg.clear(); q.clear();
		h.resize(N); h_neg.resize(N); q.resize(Q);
		for (int s = 0; s < N; ++s)
		{
			cin >> h[s];
			h_neg[s] = -h[s];
		}
			
		RMQ rmq_min(h);
		RMQ rmq_max(h_neg);
		for (int r = 0; r < Q; ++r)
		{
			q[r].resize(2);
			cin >> q[r][0] >> q[r][1];
			int minh = rmq_min.query(q[r][0], q[r][1]);
			int maxh = -rmq_max.query(q[r][0], q[r][1]);
			cout << maxh - minh << endl;
		}

		

		
		
		
	}
}