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
bool can[301][103][103][103];
int main()
{
        int n, c1, c2, c3;
        scanf("%d %d %d %d", &n, &c1, &c2, &c3);
        c1 = min(c1, 102);
        c2 = min(c2, 102);
        c3 = min(c3, 102);

        vi b(n);
        rep(i,0,n) scanf("%d", &b[i]);
        int sum = accumulate(b.begin(), b.end(), 0);

        vector<bool> edge(sum + 1);
        int q = 0;
        rep(i,0,n-1)
        {
            q += b[i];
            edge[q] = true;
        }

        memset(can, 0x00, sizeof(can));
        can[0][0][0][0] = true;

        rep(i,0,sum)
            rep(j,0,c1+1) rep(k,0,c2+1) rep(l,0,c3+1)
            if (can[i][j][k][l])
            {
                if (j < c1)
                {
                    if (!edge[i + 1])
                        can[i + 1][j + 1][k][l] = true;
                }
                if (k < c2 && i + 2 <= sum)
                {
                    if (!edge[i + 2])
                        can[i + 2][j][k + 1][l] = true;
                }
                if (l < c3 && i + 3 <= sum)
                {
                    if (!edge[i + 3])
                        can[i + 3][j][k][l + 1] = true;
                }
            }

        bool ok = false;
        rep(j,0,c1+1) rep(k,0,c2+1) rep(l,0,c3+1)
            if (can[sum][j][k][l])
                ok = true;
        printf("%s\n", (ok ? "YES" : "NO"));
}
