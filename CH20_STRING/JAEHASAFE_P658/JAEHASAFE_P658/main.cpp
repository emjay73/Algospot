#include "KMP.h"

#include <iostream>

using namespace std;
int main ()
{
	int nCases, nStates;
	string current, next;
	bool clockwise = true;
	cin >> nCases;

	while (nCases--)
	{
		cin >> nStates;

		cin >> current;
		int cnt = 0;
		while (nStates--)
		{
			cin >> next;

			if (clockwise)
			{
				auto kmp = kmpSearch(next + next, current);
				cnt += kmp[0];
			}
				
			else
			{
				auto kmp = kmpSearch(current + current, next);
				cnt += kmp[0];
			}				
			//cout << cnt;
			clockwise = !clockwise;
			current = next;
		}
		cout << cnt << endl;
	}
}