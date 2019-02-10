#include <iostream>
#include <cstring>

using namespace std;

constexpr int MAX_STUDENTS = 10;
int C, n, m;
bool areFriends[MAX_STUDENTS][MAX_STUDENTS];
bool selected[MAX_STUDENTS];

int countPairs(bool selected[])
{
	int idxMe = -1;
	for(int i=0; i<n; ++i)
	{
		if(!selected[i])
		{
			idxMe = i;
			break;
		}
	}
	if(idxMe < 0)
	{
		return 1;
	}

	selected[idxMe] = true;
	int ret = 0;
	for(int i = idxMe + 1; i<n; ++i)
	{
		if(!selected[i] && areFriends[idxMe][i])
		{
			selected[i] = true;
			ret += countPairs(selected);
			selected[i] = false;
		}

	}
	selected[idxMe] = false;
	return ret;
}

int main ()
{
	cin >> C;	
	while(C--)
	{
		memset(areFriends, 0, sizeof(areFriends));
		memset(selected, 0, sizeof(selected));

		cin >> n >> m;
		while(m--)
		{
			int idx1, idx2;
			cin >> idx1 >> idx2;
			areFriends[idx1][idx2] = true;
			areFriends[idx2][idx1] = true;
		}
		cout << countPairs(selected) << endl;
	}
}
