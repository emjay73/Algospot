// Balanced Binary Tree Example

#include <iostream>
#include <map>
using namespace std;

int N;
map<int, int> candis;

void removeDominated(int p, int q)
{
	auto it = candis.lower_bound(p);
	
	// p is left most element
	if (it == candis.begin()) return;
	--it;

	while (true)
	{
		if (it->second > q)
			break;
		
		if (it == candis.begin())
		{
			candis.erase(it);
			break;
		}
		else
		{
			/*auto it_rm = it;			
			--it;
			candis.erase(it_rm);*/

			auto it_temp = it;
			--it_temp;
			candis.erase(it); 
			it = it_temp;
		}
		
		
	}
	
}
bool isDominated(int p, int q)
{
	auto it = candis.lower_bound(p);
	if (it == candis.end()) return false;
	return q < it->second;
}

int registered(int p, int q)
{
	if (isDominated(p, q)) return candis.size();
	removeDominated(p, q);
	candis[p] = q;
	return candis.size();
}

int main()
{	
	int C, p, q;
	cin >> C;		
	/*cin.clear();
	std::cin.ignore(INT_MAX);*/
	
	while (C--)
	{
		cin >> N;
		long long int cnt = 0;
		candis.clear();
		for (int n = 0; n < N; ++n)
		{
			cin >> p >> q;
			cnt += registered(p, q);
		}
		cout << cnt << endl;
		
	}
}