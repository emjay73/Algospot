#include "../Treap/Treap.h"
#include <iostream>

using namespace std;

int N;
int shifted[50000] = {0, };
int A[50000] = { 0, };

void solve()
{
	Node * candidates = NULL;

	// save 1~N to treap
	for (int n = 1; n <= N; ++n)
		candidates = treap_insert(candidates, new Node(n));

	// fill A backwards
	for (int i = N - 1; i >= 0; --i)
	{
		int larger = shifted[i];
		Node * k = treap_kth(candidates, i + 1 - larger);
		A[i] = k->key;
		candidates = treap_erase(candidates, k->key);

	}

	for (int n = 0; n < N; ++n)
		cout << A[n] << " ";
	cout << endl;
	
}

int main()
{
	int C;
	cin >> C;
	while (C--)
	{
		cin >> N;
		for (int n = 0; n < N; ++n)		
			cin >> shifted[n];	
		solve();

	}
}