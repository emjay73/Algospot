#include <iostream>
#include <queue>
#include <functional>
using namespace std;
int C;

struct RNG {
	int seed, a, b;
	RNG(int _a, int _b) :a(_a), b(_b), seed(1983) {	}
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

int running_median(int n, RNG rng)
{
	// type, container, comparison
	priority_queue<int, vector<int>, less<int>> max_heap;
	priority_queue<int, vector<int>, greater<int>> min_heap;

	int ret = 0;

	for (int cnt = 1; cnt <= n; ++cnt)
	{

		// size of maxheap == size of min heap or
		// size of maxheap == size of min heap + 1
		if (max_heap.size() == min_heap.size())
			max_heap.push(rng.next());
		else
			min_heap.push(rng.next());

		
		if (!min_heap.empty() && !max_heap.empty())			
		{
			int mintop = min_heap.top();
			int maxtop = max_heap.top();
			if (mintop < maxtop)
			{
				min_heap.pop();
				max_heap.pop();
				min_heap.push(maxtop);
				max_heap.push(mintop);
			}			
		}

		ret = (ret + max_heap.top()) % 20090711;
	}
	return ret;


}

int main()
{
	int N,a, b;
	cin >> C;
	

	while (C--)
	{
		cin >> N >> a >> b;
		cout << running_median(N, RNG(a, b)) << endl;
	}
	

}