#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include "../RMQ_range_minimum_query/RMQ.h"
using namespace std;

const int MAX_N = 100000; // max family size

//each node has child
vector<vector<int>> children_of(MAX_N, vector<int>());

// each node has two kinds of index,
// one for personality, and the other for visiting order
// 1. famidx : person index == node index in the family tree
// 2. serial : =tripidx, node index given by traverse order. First visit matters only.
int famidx2serial[MAX_N];
int serial2famidx[MAX_N];

// depth of each node
int depth[MAX_N]; 

// 
int famidx2firsttripidx[MAX_N];

void preorder_traverse(int serial_number, int famidx, int node_depth, vector<int> & trip)
{
	famidx2serial[famidx       ] = serial_number;
	serial2famidx[serial_number] = famidx;
	++serial_number;

	// depth
	depth[famidx] = node_depth;

	//
	famidx2firsttripidx[famidx] = trip.size();
	trip.emplace_back(famidx2serial[famidx]);

	for (int c = 0; c < children_of[famidx].size(); ++c)
	{
		preorder_traverse(serial_number + 1, children_of[famidx][c], node_depth + 1, trip);
		trip.emplace_back(famidx2serial[famidx]);
	}
}

RMQ * prepareRMQ()
{
	int serial_number = 0;
	vector<int> trip; // save 
	preorder_traverse(serial_number, 0, 0, trip);
	return new RMQ(trip);

}

// compute degree of kinship bw you & I
int compute_family_distance(RMQ* rmq_preorder_traverse, int me, int you)
{
	int l = famidx2firsttripidx[me];
	int r = famidx2firsttripidx[you];
	if (l > r) swap(l, r);
	int common_father_serial = rmq_preorder_traverse->query(l, r);
	int common_father_famidx = serial2famidx[common_father_serial];

	return depth[you] + depth[me] - 2 * depth[common_father_famidx];


}

int main()
{
	cin.sync_with_stdio(false);

	int C;
	int N; // #people 
	int Q; // #query
	int im_your_father;
	int you, me;
	//cin >> C;
	scanf("%d\n", &C);
	while (C--)
	{
		//cin >> N >> Q;		
		scanf("%d %d\n", &N, &Q);
		//children_of.resize(N);
		children_of.assign(children_of.size(), vector<int>());
		for (int famidx = 1; famidx < N; ++famidx)
		{
			//cin >> im_your_father;
			scanf("%d\n", &im_your_father);
			children_of[im_your_father].emplace_back(famidx);
		}			
			
		RMQ* rmq = prepareRMQ();
		for (int q = 0; q < Q; ++q)
		{			
			//cin >> you >> me;
			scanf("%d %d\n", &you, &me);			
			//cout << compute_family_distance(rmq, you, me) << endl;
			printf("%d\n", compute_family_distance(rmq, you, me));
			
			
		}
		delete rmq;

	}
}