// prob definition : 
// estimae tree post-order from pre-order and in-order


#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> slice(vector<int> vec, int from, int to)
{
	return vector<int>(vec.begin() + from, vec.begin() + to);
}
void estimate_post_order(vector<int> preo, vector<int> ino)
{
	if (preo.empty()) return;
	
	auto r = preo[0];
	auto it = find(ino.begin(), ino.end(), r);
	auto N = ino.size();
	auto L = distance(ino.begin(), it);
	auto R = distance(it, ino.end())-1;	

	estimate_post_order(slice(preo, 1, L+1), slice(ino, 0, L));	
	estimate_post_order(slice(preo, L+1, N), slice(ino, L+1, N));
	cout << r << " ";	
}
int main()
{
	int C, N;
	cin >> C;

	while (C--)
	{
		cin >> N;
		vector<int> preorder(N), inorder(N);
		for (int n = 0; n < N; ++n)		
			cin >> preorder[n];
		for (int n = 0; n < N; ++n)
			cin >> inorder[n];
		estimate_post_order(preorder, inorder);
		cout << endl;
		
	}
}