#include <iostream>
#include <cstring>
#include <vector>
#include <limits>
#include <algorithm>
#include <cassert>
using namespace std;

const double EPS=0;
const double INF = numeric_limits<double>::infinity();
inline bool EQ (double x, double y) {return abs(x-y)<=EPS;}
inline bool LT (double x, double y) {return x+EPS<y;}
inline bool LE (double x, double y) {return x-EPS<=y;}
inline double sq(double x) {return x*x;}

struct pt {
  double x,y;
  pt() {}
  pt(double x_, double y_) : x(x_), y(y_) {}
  pt operator + (const pt& p) const { return pt(x+p.x,y+p.y); }
  pt operator - (const pt& p) const { return pt(x-p.x,y-p.y); }
  pt operator * (double l) const { return pt(x*l,y*l); }
  pt operator / (double l) const { return pt(x/l,y/l); }
  double operator * (const pt& p) const { return x*p.x+y*p.y; }
  double operator ^ (const pt& p) const { return x*p.y-y*p.x; }
  double mod2() const { return (*this)*(*this); }
  bool operator < (const pt& p) const {
    if (not EQ(x,p.x)) return x<p.x;
    return LT(y,p.y);
  }
};
bool left (const pt& v1, const pt& v2) { return LT(0,(v1^v2)); }
bool left (const pt& p1, const pt& p2, const pt& p3) { return left(p2-p1,p3-p2); }
bool lefteq (const pt& v1, const pt& v2) { return LE(0,(v1^v2)); }
bool lefteq (const pt& p1, const pt& p2, const pt& p3) { return lefteq(p2-p1,p3-p2); }
bool aligned (const pt& v1, const pt& v2) { return EQ(0,(v1^v2)); }
bool aligned (const pt& p1, const pt& p2, const pt& p3) {
  return aligned(p2-p1,p3-p2);
}

istream& operator >> (istream& i, pt& p) { return i >> p.x >> p.y; }
ostream& operator << (ostream& o, const pt& p) { return o << p.x << ' ' << p.y; }

template<typename T> istream& operator >> (istream& i, vector<T>& v) {
  int n;
  i >> n;
  v.resize(n);
  for (auto& x : v) i >> x;
  return i;
}
template<typename T> ostream& operator << (ostream& o, const vector<T>& v) {
  for (const auto& x : v) o << x << ' ';
  return o;
}

typedef vector<pt> VP;

// input is lexicographically sorted
VP ch(const VP& p) {
  int n=p.size();
  VP h;
  int h1=-1;
  for (int i=0;i<n;++i) {
    while(h1>0 && !lefteq(h[h1-1],h[h1],p[i])) {
      h.pop_back();h1--;
    }
    h.push_back(p[i]);h1++;
  }
  int h2=0;
  for (int i=n-2;i>=0;--i) {
    while(h2>0 && !lefteq(h[h1+h2-1],h[h1+h2],p[i])) {
      h.pop_back();h2--;
    }
    h.push_back(p[i]);h2++;
  }
  h.pop_back(); //leftmost
  return h;
}

int n;
int dp[1001][1001];
int naligned[1001];

int get(int a, int d) {
  if (d<0) return 0;
  a%=n;
  int& x=dp[a][d];
  if (x!=-1) return x;
  if (d<=naligned[a]) return x=1;
  x=get(a+naligned[a]+1,d-naligned[a]-1);
  x=min(x,get(a+1,d-2));
  for (int i=naligned[a]+1;i<d;++i) {
    x=min(x,get(a+1,i-2)+get(a+i+1,d-i-1));
  }
  return ++x;
}

void mkaligned(const VP& v) {
  for (int i=0;i<n;++i) {
    for (int d=2;d<n;++d) {
      if (not aligned(v[i],v[(i+1)%n],v[(i+d)%n])) {
        naligned[i]=d-1;
        break;
      }
    }
  }
}

int main() {
  memset(dp,-1,sizeof(dp));
  VP v;
  cin >> v;
  n=v.size();
  sort(v.begin(),v.end());
  v=ch(v);
  assert(n==v.size());
  mkaligned(v);
  cout << get(0,n-1) << endl;
}
