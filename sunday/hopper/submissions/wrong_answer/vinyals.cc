#include <iostream>
#include <cstring>
using namespace std;

const int INF=1<<29;

int dp[10002][2187][3];
int g[10001][8]; // edges pointing to the left
int a[10000];
int n,d,m;

void decode(int mask, int ret[]) {
  for (int i=0;i<d;++i) {
    ret[i]=mask%3;
    mask/=3;
  }
}

int shift[]={0,1,3,9,27,81,243,729};

int get(const int i, const int edgemask, const int endpoints) {
  cerr << i << ' ' << edgemask << ' ' << endpoints << endl;
  int& x = dp[i+1][edgemask][endpoints];
  if (x!=-1) return x;
  if (edgemask==0 and endpoints==0) return x=0;
  x=-INF;
  if (i==-1) return x;
  int ni=i-1;
  int edges[7];
  decode(edgemask,edges);
  if (edges[d-1]==2) return x;
  for (int j=0;j<=d;++j) { // right edge
    if (edges[d-1]==1 and j!=d) continue;
    if (j) {
      if (not edges[j-1]) continue;
      if (not g[i+j][j]) continue;
    }
    for (int jj=0;jj<(j?j:1);++jj) { // 2nd right edge
      if (jj) {
        if (not edges[jj-1]) continue;
        if (not g[i+jj][jj]) continue;
      }
      for (int k=0;k<=2;++k) { // left edges
        //if (k==2 and endpoints!=2) continue;
        int nedgemask=edgemask;
        int nendpoints=endpoints;
        int degree=k;
        if (j) degree++;
        if (jj) degree++;
        if (degree>2) continue;
        if (degree==1) nendpoints--;
        if (nendpoints<0) continue;
        nedgemask-=shift[j];
        nedgemask-=shift[jj];
        //if (nedgemask==0 and edgemask and endpoints) continue;
        nedgemask*=3;
        nedgemask+=k;
        x=max(x,degree+get(ni,nedgemask,nendpoints));
      }
    }
  }
  return x;
}

int moin() {
  memset(dp,-1,sizeof(dp));
  cin >> n >> d >> m;
  for (int i=0;i<n;++i) {
    cin >> a[i];
    for (int j=1;j<=d;++j) {
      g[i][j] = (j<=i and abs(a[i]-a[i-j])<=m);
    }
  }
  for (int j=1;j<=d;++j) g[n][j]=0;
  cout << get(n,0,2)/2+1 << endl;
}

int main() {
  int k;
  cin >> k;
  while(k--) moin();
}
