#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> fence;
int solve(int left, int right)
{
	if(left==right)
		return fence[left];

	int ret = 0;
	int half = (left + right)/2;
	ret = max(solve(left, half), solve(half+1, right));

	int l = half, r = half+1;
	int height = min(fence[l], fence[r]);
	
	ret = max(height * 2, ret);

	while(l > left || r < right)
	{
		if((l>left) && (r == right || (fence[r+1] < fence[l-1])))
		{
			--l;
			height = min(fence[l], height);
		}
		else 
		{
			++r;
			height = min(fence[r], height);
		}
		
		ret = max(ret, (r-l+1) * height);
	}
	
	return ret;
}

int main ()
{
	int C;
	cin >> C;

	while(C--)
	{
		fence.clear();

		int nf, el;
		cin >> nf;
		while(nf--)
		{
			cin >> el;
			fence.emplace_back(el);
		}

		cout << solve(0, fence.size()-1) << endl;
	}
}
