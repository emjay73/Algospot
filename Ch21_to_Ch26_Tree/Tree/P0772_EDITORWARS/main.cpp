#include "../UnionFind/UnionFind.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M;

struct BipartiteUnionFind:NaiveDisjointSet 
{
	//vector<int> parent; // of element
	//vector<int> rank; // depth (has value only if index equals root)
	vector<int> size;	// # node (has value only if index equals root)
	vector<int> enemy;	// root of enemy (has value only if index equals root, otherwise, -1)

	BipartiteUnionFind(int n)
		:NaiveDisjointSet(n),
		 size(n, 1),
		 enemy(n, -1)		
	{		
	}
	
	// a and b are same set
	// so merge sets (a set--> b set)
	// return new root
	int merge_set(int a, int b)
	{
		if (a == -1 || b == -1) return max(a, b);

		// find root of each set
		int ra = find_set(a), rb = find_set(b);

		// already same set
		if (ra == rb) return ra;
		if (rank[ra] > rank[rb]) swap(ra, rb);
		parent[ra] = rb;
		
		// only in this case, depth increases by 1
		if (rank[ra] == rank[rb]) ++rank[rb];

		// update size
		size[rb] += size[ra];

		// return new root
		return rb;
	}

	// a and b hate each other
	bool dis(int a, int b)
	{
		int ra = find_set(a);
		int rb = find_set(b);

		// paradox!
		if (ra == rb) return false;

		int g1 = merge_set(ra, enemy[rb]);
		int g2 = merge_set(rb, enemy[ra]);

		enemy[g1] = g2;
		enemy[g2] = g1;

		return true;
	}

	// a and b love each other
	bool ack(int a, int b)
	{
		int ra = find_set(a);
		int rb = find_set(b);

		// paradox!
		//if (ra != rb) return false;
		if (enemy[ra] == rb) return false;

		int g1 = merge_set(ra, rb);
		int g2 = merge_set(enemy[ra], enemy[rb]);
		enemy[g1] = g2;

		// if there's group that g1 hates,,,
		if (g2 != -1) enemy[g2] = g1;

		return true;


	}
	
	
};

int max_party_size(const BipartiteUnionFind& buf)
{
	int ret = 0;
	for (int node = 0; node < N; ++node)
	{
		// find root
		if (buf.parent[node] != node) continue;

		int enemy = buf.enemy[node];

		// to avoid duplicated counting
		if (enemy > node) continue;

		int root_size = buf.size[node];
		int enem_size = enemy == -1 ? 0 : buf.size[enemy];

		// people with no tendency would be added
		ret += max(root_size, enem_size);		

	}

	return ret;
}

int main()
{
	int C;
	int idxa, idxb; // humans
	string stance;

	cin >> C;
	while (C--)
	{		
		cin >> N >> M;

		BipartiteUnionFind buf(N);

		bool paradox = true;
		for (int m = 0; m < M; ++m)
		{
			cin >> stance >> idxa >> idxb;
			if (stance == "ACK")
			{
				paradox = !buf.ack(idxa, idxb);
				if (paradox)
				{
					cout << "CONTRADICTION AT " << m + 1 << endl;
					break;
				}
					
			}				
			else
			{
				paradox = !buf.dis(idxa, idxb);
				if (paradox)
				{
					cout << "CONTRADICTION AT " << m + 1 << endl;
					break;
				}
					
			}

		}
		if (paradox) continue;
		cout << "MAX PARTY SIZE IS " << max_party_size(buf) << endl;
		


	}


}