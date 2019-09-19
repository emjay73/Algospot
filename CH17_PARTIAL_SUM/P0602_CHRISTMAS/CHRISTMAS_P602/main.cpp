#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

constexpr int MAXK = 100000;
constexpr int MAXN = 100000;
constexpr int MAXD = 100000;
constexpr int MOD = 20091101;

int K;  // kids
int N;	// boxes
int D;	// doll

int box[MAXN+1];
//int accumbox[MAXN+1];
int modabox[MAXN+1];
using namespace std;

int waysToBuy(int modabox[]);
int maxBuys(int modabox[]);

int main()
{
	int C;
	cin >> C;

	while (C--)
	{
		cin >> N >> K;
		//memset(box, 0, sizeof(box));
		box[0] = 0;
		//accumbox[0] = 0;
		modabox[0] = 0;
		for (int b = 1; b <= N; ++b)
		{
			cin >> box[b];
			//accumbox[b] = accumbox[b-1] + box[b];
			//modabox[b] = accumbox[b]%K;
			modabox[b] = (modabox[b-1] + (box[b] % K)) % K;

		}			

		cout << waysToBuy(modabox) << " " << maxBuys(modabox) << endl;
		
	}
}

int waysToBuy(int modabox[])
{
	int ways = 0;
	vector<int> cntmod(K, 0);

	for (int i = 0; i <= N; ++i)
		++cntmod[modabox[i]];

	for (auto c : cntmod)
	{
		if (c <= 1) continue;
		ways = (ways + ((static_cast<long long>(c) * (c-1)) / 2)) % MOD;
	}

	return ways;
}

int maxBuys(int modabox[])
{
	vector<int> maxbuys(N + 1, 0);
	vector<int> lastseen(K, -1);	
		
	for (int i = 0; i <= N; ++i)
	{
		if(i) maxbuys[i] = maxbuys[i - 1];
		else maxbuys[i] = 0;

		int ipair = lastseen[ modabox[i] ];
		lastseen[modabox[i]] = i;
		if (ipair != -1) maxbuys[i] = max(maxbuys[i], maxbuys[ipair] + 1);
	}
	return maxbuys.back();
}
