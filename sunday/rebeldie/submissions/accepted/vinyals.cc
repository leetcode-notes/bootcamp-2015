#include <iostream>
#include <unordered_set>
#include <cassert>
#include <cstdio>
using namespace std;

typedef unordered_set<uint> SI;

int m,n;
SI seen[100][100];
int board[100][100];

int di[]={0,1,0,-1};
int dj[]={1,0,-1,0};

//   4
// 3 0 1 2
//   5

int sigma[][6] = {
  {3,0,1,2,4,5}, //right
  {4,1,5,3,2,0}, //down
  {1,2,3,0,4,5}, //left
  {5,1,4,3,0,2}, //up
};

void decode(uint paint, int* colours) {
  for (int i=0;i<6;++i) {
    colours[i]=paint&0x1f;
    paint>>=5;
  }
}

uint encode(int* colours) {
  uint paint=0;
  for (int i=5;i>=0;--i) {
    paint<<=5;
    paint|=colours[i];
  }
  return paint;
}

uint rot(uint paint, int k) {
  int colours[6], newcolours[6];
  decode(paint,colours);
  for (int i=0;i<6;++i) newcolours[i]=colours[sigma[k][i]];
  return encode(newcolours);
}

void draw(uint paint) {
  int colours[6];
  decode(paint,colours);
  fprintf(stderr, "   %2d\n%2d %2d %2d %2d\n   %2d\n",
         colours[4],colours[3],colours[0],colours[1],colours[2],colours[5]);
}

bool dfs(int i, int j, uint paint) {
  int thiscolour=paint&0x1f;
  if(thiscolour==0x1f) {
    paint^=0x1f;
    paint|=board[i][j];
  }
  else if (thiscolour!=board[i][j]) return false;
  if (i==m-1 and j==n-1) return true;
  if (not seen[i][j].insert(paint).second) return false;
  for (int k=0;k<4;++k) {
    int ii=i+di[k];
    int jj=j+dj[k];
    if (ii<0 or ii>=m or jj<0 or jj>=n) continue;
    if (dfs(ii,jj,rot(paint,k))) return true;
  }
  return false;
}

int main() {
  //test();exit(0);
  cin >> m >> n;
  for (int i=0;i<m;++i) {
    for (int j=0;j<n;++j) {
      cin >> board[i][j];
    }
  }
  cout << (dfs(0,0,0x3fffffff) ? "YES" : "NO") << endl;
}

void test() {
  for (int i=0;i<1000;++i) {
    uint paint=rand()&0x3fffffff;
    int colours[6];
    decode(paint,colours);
    assert (paint==encode(colours));
    for (int k=0;k<4;++k) {
      uint ipaint=paint;
      for (int q=0;q<4;++q) paint=rot(paint,k);
      assert(paint==ipaint);
      paint=rot(rot(paint,k),(k+2)%4);
      assert(paint==ipaint);
    }
  }
}
