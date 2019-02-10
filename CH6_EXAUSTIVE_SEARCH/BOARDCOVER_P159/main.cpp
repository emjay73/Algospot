#include <cstring>
#include <iostream>

using namespace std;

constexpr int MAX_SIZE = 20;
int covertype[4][3][2] = 
{
{{0,0},{1, 0},{0, 1}},
{{0,0},{1, 0},{1, 1}},
{{0,0},{0, 1},{1, 1}},
{{0,0},{0, 1},{-1, 1}},
};

int BOARD[MAX_SIZE][MAX_SIZE];
char row[MAX_SIZE];
int W, H;

void printB()
{
  cout << "------------------------------" << endl;
  for(int iy=0; iy<H; ++iy)
  {
    for(int ix=0; ix<W; ++ix)
    {
      cout << BOARD[iy][ix] << " ";
    }
    cout << endl;
  }
  cout << "------------------------------" << endl;

}

bool set(int BOARD[][MAX_SIZE], int iy, int ix, int type, int put)
{
  bool ret = true;
  //int *ctype[2] = covertype[type];
  for(int ib=0; ib<3; ib++)
  {
    int newy = iy + covertype[type][ib][1];
    int newx = ix + covertype[type][ib][0];

    if( newy < 0 || newy >= H || 
        newx < 0 || newx >= W ||
        (BOARD[newy][newx]+=put) > 1)
      ret = false;
  }

  return ret;

}

int cover(int BOARD[][MAX_SIZE])
{

//  int ret = 0;
  int iy, ix;
  bool found = false;
	for(iy = 0; iy < H; ++iy)
	{
    for(ix = 0; ix < W; ++ix)
    {
      	if(!BOARD[iy][ix])			
        {
			    found = true;
          break;
        }
    }
    if(found)
      break;
	}	

  if(!found)
    return 1;

  int ret = 0;
	for(int type=0; type<4; ++type)
  {
    //cout << "type, iy, ix : " << type << " " << iy << " " << ix << endl;
    if(set(BOARD, iy, ix, type, 1))
    {
      ret += cover(BOARD); 
    }

    //printB(); 
    set(BOARD, iy, ix, type, -1);
    //printB();
	}

  return ret;
}

int main ()
{
	int C;
	cin >>C;
	while(C--)
	{
    memset(BOARD, 0, sizeof(BOARD));
		int cntEmpty = 0;
		cin >> H >> W;
		
		cin.ignore(100, '\n');
		for(int h=0; h<H; ++h)
		{
			fgets(row, MAX_SIZE, stdin);
			for(int w = 0; w<W; ++w)
			{
				if(row[w] == '#')
					BOARD[h][w] = 1;
				else
				{
					BOARD[h][w] = 0;
					++cntEmpty;
				}
			}
		}
//    printB(BOARD);
		if(cntEmpty%3)
			cout << 0 << endl;
		else
			cout << cover(BOARD) << endl; 
	}
}
