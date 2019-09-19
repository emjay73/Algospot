#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int INF = 987654321;
constexpr int MAXN = 12;
constexpr int MAXK = MAXN;
constexpr int MAXM = 10;
constexpr int MAXL = 10;

int N, K, M, L;
int pre[MAXN];
int sem[MAXM];	// semester

int cache[MAXM][1<<MAXN];
int graduate(int semester, int taken);
int bitcnt(int n);
int main()
{
	/*ifstream ifs;
	ifs.open("C:/Users/emjay/Documents/Programming/GRADUATION_P590/GRADUATION_P590/test.txt");*/
	
	int nCase;
	//ifs >> nCase;
	cin >> nCase;

	
	

	while(nCase--)
	{
		//ifs >> N >> K >> M >> L;
		cin >> N >> K >> M >> L;
		memset(pre, 0, sizeof(pre));
		memset(sem, 0, sizeof(sem));
		memset(cache, -1, sizeof(cache));
		
		// loop major
		int npre = 0, temp;
		for (int n = 0; n < N; n++)
		{
			//ifs >> npre;
			cin >> npre;

			while (npre--)
			{
				
				//ifs >> temp;
				cin >> temp;
				pre[n] |= (1 << temp);
			}
			
		}

		// loop semester
		int nclass;
		for (int m = 0; m < M; ++m)
		{
			
			//ifs >> nclass;
			cin >> nclass;
			while (nclass--)
			{
				//ifs >> temp;
				cin >> temp;
				sem[m] |= (1 << temp);
			}
		}

		int result;
		if ((result = graduate(0, 0)) == INF)
			std::cout << "IMPOSSIBLE" << std::endl;
		else
			std::cout << result << std::endl;


	}

	//ifs.close();
}

int graduate(int semester, int taken)
{
	if (bitcnt(taken) >= K) return 0;

	if (semester == M) return INF;

	int & ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;

	int canTake = (sem[semester] & ~taken);

	for (int i = 0; i < N; ++i)
	{
		if ((canTake & (1 << i)) &&
			(taken & pre[i]) != pre[i])
			canTake &= ~(1 << i);

	}

	for (int take = canTake; take > 0; take = (take-1)&canTake)
	{
		if (bitcnt(take) > L) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}

	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}

int bitcnt(int n)
{
	unsigned int un = static_cast<unsigned int>(n);

	int cnt = 0;
	while (un)
	{
		if (un & 1) 
			++cnt;
		un = un >> 1;
	}

	return cnt;
}