#include <iostream>
#include <cstring>
#include <unordered_map>
#include <cassert>
using namespace std;

const int INF=1<<29;

typedef unordered_map<uint,int> MII;

MII dp[10002][1<<8][3];
int g[10001][8]; // edges pointing to the left
int a[10000];
int n,d,m;

void decode(uint mask, uint info, int edges[], int classof[]) {
  for (int i=0;i<d;++i) {
    edges[i]=mask&1;
    mask>>=1;
  }
  for (int i=0;i<d;++i) {
    if (info&1) {
      assert(edges[i]);
      edges[i]++;
    }
    info>>=1;
  }
  info>>=(8-d);
  for (int i=0;i<d;++i) {
    classof[i]=info&0x7;
    if (classof[i]) assert(edges[i]);
    info>>=3;
  }
}

void printstate(int i, uint edgemask, int endpoints, uint info) {
  assert ((info&edgemask)==(info&0xff));
  cerr << i << ' ';
  int nedges=0;
  for (int j=0;j<d;++j) {
    if (edgemask&1) nedges++;
    cerr << (edgemask&1);
    edgemask>>=1;
  }
  assert(edgemask==0);
  cerr << ' ' << endpoints << ' ';
  for (int j=0;j<d;++j) {
    if (info&1) nedges++;
    cerr << (info&1);
    info>>=1;
  }
  info>>=(8-d);
  cerr << ' ';
  uint nclasses=0;
  for (int j=0;j<d;++j) {
    nclasses=max(nclasses,(info&7));
    cerr << (info&7);
    info>>=3;
  }
  assert(info==0);
  assert(nedges<=7);
  assert((nedges+endpoints)%2==0);
  if (endpoints==2 and nedges==2) assert(nclasses==1);
}

uint recode(uint edgemask, uint doubleinfo, uint classinfo, int identify) {
  //cerr << "        recode " << edgemask << " " << doubleinfo << " " << classinfo << " " << identify << endl;
  int classof[7];
  int todo[7];
  for (int i=0;i<d;++i) {
    classof[i]=classinfo&0x7;
    classinfo>>=3;
    todo[i]=(edgemask&(1<<i));
  }
  uint nclassinfo=0;
  int thisclass=0;
  for (int i=0;i<d;++i) {
    if (not todo[i]) continue;
    thisclass++;
    bool itstimetoidentify = (identify!=-1 and ((classof[i]==classof[0]) or (classof[i]==identify)));
    for (int j=0;j<d;++j) {
      if (not todo[j]) continue;
      if (classof[j]==classof[i] or
          (itstimetoidentify and
           ((classof[j]==identify) or (classof[j]==classof[0])))) {
        nclassinfo|=(thisclass<<(3*j));
        todo[j]=false;
      }
    }
  }
  assert(int(doubleinfo)<(1<<d));
  return (nclassinfo<<8)|doubleinfo;
}

int shift[]={0,1,2,4,8,0x10,0x20,0x40,0x80};

void advance(const int i, const uint edgemask, const int endpoints, const uint info, int len) {
  int edges[7];
  int classof[7];
  decode(edgemask,info,edges,classof);
  //printstate(i,edgemask,endpoints,info); cerr << endl;
  if (edges[d-1]==2) return;
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
        if (classof[j-1]==classof[jj-1]) continue;
        //cerr << "Connecting " << j << " and " << jj << endl;
      }
      for (int k=0;k<=2;++k) { // left edges
        int nedgemask=edgemask;
        int nendpoints=endpoints;
        int degree=k;
        if (j) degree++;
        if (jj) degree++;
        if (degree>2) continue;
        if (degree==1) nendpoints--;
        if (nendpoints<0) continue;
        if (edges[j-1]==1) nedgemask-=shift[j];
        if (edges[jj-1]==1) nedgemask-=shift[jj];
        nedgemask<<=1;
        assert(nedgemask<(1<<d));
        if (k) nedgemask|=1;
        if (nedgemask==0 and edgemask) assert(nendpoints==0);
        uint classinfo=info;
        uint doubleinfo = info&0xff;
        classinfo^=doubleinfo;
        classinfo>>=5;
        if (j) classinfo|=classof[j-1];
        doubleinfo<<=1;
        doubleinfo&=~(1<<j);
        doubleinfo&=~(1<<jj);
        if (k==2) doubleinfo|=1;
        uint ninfo=recode(nedgemask,doubleinfo,classinfo,jj?classof[jj-1]:-1);
        int& x = dp[i][nedgemask][nendpoints][ninfo];
        x=max(x,degree+len);
      }
    }
  }
}

void build(int i) {
  for (uint edgemask=0;edgemask<(1<<d);++edgemask) {
    for (int endpoints=0;endpoints<=2;++endpoints) {
      auto& cell=dp[i+1][edgemask][endpoints];
      for (const auto& it : cell) {
        advance(i,edgemask,endpoints,it.first,it.second);
      }
      cell.clear();
    }
  }
}

int main() {
  cin >> n >> d >> m;
  int nedges=0;
  for (int i=0;i<n;++i) {
    cin >> a[i];
    for (int j=1;j<=d;++j) {
      g[i][j] = (j<=i and abs(a[i]-a[i-j])<=m);
      if (g[i][j]) nedges++;
    }
  }
  //cerr << nedges << endl;
  for (int j=1;j<=d;++j) g[n][j]=0;
  dp[n+1][0][2][0]=0;
  for (int i=n;i>=0;--i) build(i);
  cout << dp[0][0][0][0]/2+1 << endl;
  return 0;
}
