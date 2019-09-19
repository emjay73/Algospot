#include <iostream>
#include <queue>

// random number generator
struct RNG
{
	unsigned int seed;
	RNG()
		:seed(1983) {}
	unsigned int get()
	{
		unsigned int ret = seed;

		// update seed
		seed = seed * 214013u + 2531011u;
		
		return ret%10000 + 1;
	}
};

using namespace std;
int C, K, N;

int cntK();

int main()
{
	cin >> C;
	
	while (C--)
	{
		cin >> K >> N;
		cout << cntK() << endl;
	}

}

int cntK()
{
	RNG rng;
	unsigned int rangeSum = 0;
	queue<unsigned int> range;
	int cnt = 0;
	for (int i = 0; i < N; ++i)
	{
		auto sig = rng.get();
		range.push(sig);
		rangeSum += sig;

		while (rangeSum > K)
		{			
			rangeSum -= range.front();
			range.pop();
		}

		if (rangeSum == K)
			++cnt;
	}

	return cnt;
}