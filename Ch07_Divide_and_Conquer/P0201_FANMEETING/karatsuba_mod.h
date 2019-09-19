
#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;



// multiply result = sum( value * power(10, index) )
void normalize(vector<int>& num)
{

	/*num.emplace_back(0);

	for(int i=0; i<num.size()-1; ++i)
	{
		if (num[i] < 0)
		{
			int borrow = (abs(num[i]) + 9)/10;
			num[i+1] -= borrow;
			num[i] += borrow * 10;
		}

		else
		{
			num[i+1] += num[i] / 10;
			num[i] %= 10;
		}
	}

	while (!num.empty() && num.back() == 0) num.pop_back();*/
	
}

vector<int> multiply(const vector<int> & a, const vector<int> & b)
{
	vector<int> c(a.size() + b.size() + 1, 0);
	for(int i=0; i<a.size(); ++i)
	{
		for(int j=0; j<b.size(); ++j)
		{
			c[i+j] += a[i] * b[j];
		}
	}

	normalize(c);
	return c;
}


// assume a > b
// a+=b*(10^k)
void addTo(vector<int> & a, const vector<int> & b, int k)
{
	if (a.size() < k+  b.size())
		a.resize(k+ b.size(), 0);
	for (int i = 0; i < b.size(); ++i)
		a[i + k] += b[i];// *pow(10, k);
	
	normalize(a);
}

// assume a > b
// a-= b
void subFrom (vector <int> & a, const vector<int> & b)
{
	for(int i=0; i<b.size(); ++i)
		a[i] -=b[i];

	normalize(a);
}

vector<int> karatsuba(vector<int> & A, vector<int> & B)
{

	/*cout << "A" << endl;
	for (auto a : A)
		cout << a << " ";
	cout << endl;

	cout << "B" << endl;
	for (auto b : B)
		cout << b << " ";
	cout << endl;
*/

	int an = A.size();
	int bn = B.size();

	if(an < bn) return karatsuba(B, A);
	if(an == 0 || bn == 0) return vector<int>();

	if(an <= 50) return multiply(A, B);

	int half = an /2;

	vector<int> a0(A.begin(), A.begin() + half);
	vector<int> a1(A.begin() + half, A.end());
	vector<int> b0(B.begin(), B.begin() + min<int>(B.size(), half));
	vector<int> b1(B.begin() + min<int> (B.size(), half), B.end());

	// z2 = a1 * b1;
	vector<int> z2 = karatsuba(a1, b1);

	//z0 = a0 * b0;
	vector<int> z0 = karatsuba(a0, b0);

	// a0 = a0 + a1, b0 = b0 + b1
	addTo(a0, a1, 0); addTo(b0, b1, 0);

	//z1 = (a0 * b0) - z0 - z2
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	// ret = z0 + z1 * 10^half + z2 * 10^(half * 2)
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);

	return ret;


}
