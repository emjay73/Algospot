#include <iostream>
#include <vector>
using namespace std;

int compute_family_distance(
	vector<int> & im_your_father, int from, int to)
{
	
}

int main()
{
	int C;
	int N; // #people 
	int Q; // #query
	vector<int> im_your_father;
	vector<vector<int>> query;
	cin >> C;
	while (C--)
	{
		cin >> N >> Q;
		im_your_father.resize(N-1);
		query.resize(Q);

		for (int n = 0; n < N; ++n)
			cin >> im_your_father[n];

		
		for (int q = 0; q < Q; ++q)
		{
			query[q].resize(2);
			cin >> query[q][0] >> query[q][1];
			cout << compute_family_distance(im_your_father, query[q][0], query[q][1]) << endl;
			svn
		}

	}
}