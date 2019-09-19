#include <iostream>
#include <list>

using namespace std;

int N, K;

void Josephus();
int main()
{
	int C;

	cin >> C;

	while (C--)
	{
		cin >> N >> K;
		Josephus();
	}

}

void Josephus()
{
	list<int> people;

	for (int i = 1; i <= N; ++i)
		people.emplace_back(i);

	int size = N;
	list<int>::iterator kill = people.begin();
	while (size > 2)
	{
		kill = people.erase(kill);
		if (kill == people.end()) kill = people.begin();

		--size;
		
		for (int i = 0; i < K-1; ++i)
		{
			++kill;
			if (kill == people.end()) kill = people.begin();
		}
			
	}

	cout << people.front() << " " << people.back() << endl;
	
}