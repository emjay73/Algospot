// prob def : 
// find farthest node to node distance

#include "../Tree/tree_emjay.h"
#include <cmath>
int C, N;
vector<vector<int>> castle;
int longest = 0;

int sqr(int a)
{
	return pow(a, 2);
}
int sqrdist(int a, int b)
{
	return sqr(castle[a][0] - castle[b][0]) + sqr(castle[a][1] - castle[b][1]);
}

bool encloses(int a, int b)
{
	return	castle[a][2] > castle[b][2] && 
			sqrdist(a, b) < sqr(castle[a][2]-castle[b][2]);
}

bool is_child(int r, int c)
{
	if (!encloses(r, c)) return false;

	for (int i = 0; i < N; ++i)
	{
		if (i != r && i != c && encloses(r, i) && encloses(i, c))
			return false;
	}
	return true;
}
TreeNode* make_castle_tree(int r)
{	
	TreeNode* root = new TreeNode();

	for (int i = 0; i < N; ++i)
	{
		if (is_child(r, i))
			root->children.emplace_back(make_castle_tree(i));		
	}

	return root;
}

int compute_height(TreeNode* root)
{
	if (root->children.empty()) return 0;

	vector<int> heights;
	for (int c = 0; c < root->children.size(); ++c)
		heights.emplace_back(compute_height(root->children[c]));

	sort(heights.begin(), heights.end());

	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	
	return heights.back() + 1;
	
}

int main()
{
	cin >> C;
	

	while (C--)
	{
		cin >> N;
		castle.resize(N);
		longest = 0;
		for (int n = 0; n < N; ++n)
		{
			
			castle[n].resize(3);
			cin >> castle[n][0]; //x
			cin >> castle[n][1]; //y
			cin >> castle[n][2]; //r
		}

		sort(castle.begin(), castle.end(), [&](vector<int>& i, vector<int>& j) { return i[2] > j[2]; });
		auto castle_tree = make_castle_tree(0);
		auto h = compute_height(castle_tree);

		cout << max(longest, h) << endl;
	}
}