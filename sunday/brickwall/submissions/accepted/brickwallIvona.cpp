#include <stdio.h>

#define MAXP 3
#define MAXL 3
#define MAXN 105

int bottom[MAXN];
int len[MAXP],c[MAXP];
char S[MAXL*MAXN][MAXN][MAXN][MAXN]; // s[l,i,j,k] = can do length l with i,j,k remaining pieces of length len[0],len[1],len[2]

int N; // number pieces in the bottom row

int main() {
    int kk,i,j,k,l,t,sumlen,sumsofar,foundsol,tmp0,tmp1,tmp2,aligned;
    
    len[0] = 1;
    len[1] = 2;
    len[2] = 3; 
    
        scanf("%d %d %d %d",&N,&c[0],&c[1],&c[2]);
        sumlen = 0;
        for (i=0; i<N; i++) {
            scanf("%d",&bottom[i]);
            sumlen += bottom[i];    
        }
        
        // printf("c[0] = %d, c[1] = %d, c[2] = %d, sumlen = %d\n",c[0],c[1],c[2],sumlen);
        
        // base case: for length 0, possible with any number pieces
        for (i=0; i<=c[0]; i++) {
            for (j=0; j<=c[1]; j++) {
                for (k=0; k<=c[2]; k++) {
                    S[0][i][j][k] = 1;
                }
            }
        }
        
        // t: last bottom piece such that sum pieces without this < l, with this >= l
        t = 0;
        sumsofar = bottom[0];
        bottom[N-1]++; // so that we can get alignment at the end, pretend that it is not aligned
        foundsol = 0;
        for (l=1; l<=sumlen && !foundsol; l++) {
            aligned = 0;
            // printf("l = %d, sumsofar = %d\n",l,sumsofar);
            if (l==sumsofar) {
               aligned = 1;
               t++;
               sumsofar += bottom[t];
            }
            for (i=0; i<=c[0] && !foundsol; i++) {
                for (j=0; j<=c[1] && !foundsol; j++) {
                    for (k=0; k<=c[2] && !foundsol; k++) {
                        if (aligned) {
                           S[l][i][j][k] = 0;
                        } else {
                           if (i>0 && l>=len[0]) tmp0 = S[l-len[0]][i-1][j][k];
                           else tmp0 = 0;
                           if (j>0 && l>=len[1]) tmp1 = S[l-len[1]][i][j-1][k];
                           else tmp1 = 0;
                           if (k>0 && l>=len[2]) tmp2 = S[l-len[2]][i][j][k-1];
                           else tmp2 = 0;
                           S[l][i][j][k] = tmp0 || tmp1 || tmp2;   
                        }
                        if (l == sumlen && S[l][i][j][k]) foundsol = 1;
                        
                        // printf("S[%d,%d,%d,%d] = %d\n",l,i,j,k,S[l][i][j][k]);
                    }
                }             
            }
            
            // S[l,i,j,k] = OR{S[l-len[0],i-1,j,k,S[l-len[1],i,j-1,k],S[l-len[2],i,j,k-1]}
            // assumption: l-len[?] not a breaking point in bottom
        }
        
        if (foundsol) printf("YES\n");
        else printf("NO\n");
    
    return 0;
}
