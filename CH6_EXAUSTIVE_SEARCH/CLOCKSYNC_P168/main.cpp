#include <iostream>
#include <vector>

using namespace std;

constexpr int INF = 987654321;


int C;
int status[16];
bool switches[10][16] = 
{
{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
{0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}
};

void push_button(int status[], int sw, int ptime)
{
  for(int i=0; i<16; ++i)
  {
    if (switches[sw][i])
    {
      status[i] += ptime * 3;
      if(!(status[i] %= 12))
		status[i] = 12;
    }
  }
}

void print_status()
{
	for(int i=0; i<16; ++i)
	{
		cout << status[i] << " ";
	}
	cout << endl;
}

int min_push(int status[], int sw, int pushed)
{
  int idx=0;
  for(idx=0; idx<16; ++idx)
  {
    if(status[idx] !=12)
      break;
  }
  if(idx == 16)
    return pushed;

  if(sw >9) return INF;
  int ret = INF;

  for(int p=0; p<4; ++p)
  {
//	  if(sw == 8 && p == 2)
//		  cout << "break" << endl;
	  //print_status();
      push_button(status, sw, p);
	  //print_status();
      ret = min(ret, min_push(status, sw+1, pushed + p));
      push_button(status, sw, 4-p);
	  //print_status();

	 // cout << "sw, p, ret : " << sw << " " << p << " " << ret << endl;
  }

  return ret;
}
int main ()
{


  cin >> C;
  while(C--)
  {
    for(int s=0; s<16; ++s)
    {
      cin >> status[s];
	  //cout << status[s] << " " ;
    }

    int ret =min_push(status, 0, 0) ;
    if(ret == INF)
    	cout << -1 << endl;
    else
    	cout << ret << endl;

  }
}
