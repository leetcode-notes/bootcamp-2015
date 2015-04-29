//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <bitset>
#include <utility>
#include <list>
#include <numeric>

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int main()
{
        int n; scanf("%d", &n);
        vi x(n), y(n);
        rep(i,0,n)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            x[a]++;
            y[b]++;
        }

        ll res = 0;
        int rx = x[0], ry = y[0];
        rep(i,1,n)
        {
            res += abs(rx - i);
            res += abs(ry - i);
            rx += x[i];
            ry += y[i];
        }
        cout << res << endl;
}
