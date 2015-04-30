#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000
#define MC 100

const int deltar[] = {0, 0, -1, 1}; // directions on the board: 0: left, 1: right, 2: up, 3: down
const int deltac[] = {-1, 1, 0, 0};

struct dierot {
    int cs,l,r,u,d,b; // current side, who's on the left/right/up/down/bottom
};

int board[MAX][MAX];
int seen[MAX][MAX][6][6]; // current side plus the side above it (up)
int die[6];
int M,N;

int col[MC];

/*
4
0 1 2 3
5
*/

struct dierot turn(struct dierot cur, int dirturn) {
     struct dierot dienew;
     
     switch (dirturn) {
       case 0: // left
            dienew.cs = cur.r;
            dienew.u = cur.u;
            dienew.d = cur.d;
            dienew.l = cur.cs;
            dienew.r = cur.b;
            dienew.b = cur.l;
            return dienew;
       case 1: // right
            dienew.cs = cur.l;
            dienew.u = cur.u;
            dienew.d = cur.d;
            dienew.r = cur.cs;
            dienew.l = cur.b;
            dienew.b = cur.r;
            return dienew;            
       case 2: // up
            dienew.cs = cur.d;
            dienew.u = cur.cs;
            dienew.b = cur.u;
            dienew.l = cur.l;
            dienew.r = cur.r;
            dienew.d = cur.b;
            return dienew;            
       case 3: // down
            dienew.cs = cur.u;
            dienew.d = cur.cs;
            dienew.b = cur.d;
            dienew.l = cur.l;
            dienew.r = cur.r;
            dienew.u = cur.b;
            return dienew;
     }
     abort();
}
       
int roll(int i, int j, struct dierot d) {
    int p,ss,possible,ii,jj;
    struct dierot dn;
    
    // check out of bounds
    if (i<0 || i>=M || j<0 || j>=N) return 0;
    
    // check color
    if (die[d.cs] != board[i][j]) return 0;
    
    // check if destination
    if (i==M-1 && j==N-1) return 1;
    
    seen[i][j][d.cs][d.u] = 1;
    
    // try rolling in the four directions
    // p - directions wrt to the board
    for (p=0; p<4; p++) {
        // printf("trying direction p = %d\n",p);
        dn = turn(d,p);
        ii = i+deltar[p];
        jj = j+deltac[p];
        // printf("ii = %d, jj = %d, ss = %d\n",ii,jj,dn.cs);
        if (ii<0 || ii>=M || jj<0 || jj>=N) continue;
        if (!seen[ii][jj][dn.cs][dn.u]) {
           if (roll(ii,jj,dn)) return 1;
        }
    }
    
    return 0;
}

int cmpfnc(const void *a, const void *b) {
   return (*(int*)a - *(int*)b);
}

int main() {
    int k,i,j,s,p,c,cc,possible,colcount,u;
    struct dierot dd;
    
    scanf("%d",&k);
    for (; k>0; k--) {
        scanf("%d %d ",&M,&N);
        for (i=0; i<MC; i++) col[i] = MC;
        colcount = 0;
        
        for (i=0; i<M; i++) {
            for (j=0; j<N; j++) {
                scanf("%d",&board[i][j]);
                if (col[board[i][j]]==MC) {
                   col[board[i][j]] = board[i][j];
                   colcount++;
                }
            }
            qsort(col,colcount,sizeof(int),cmpfnc);
        }
        
        // check special cases M=1 or N=1
        if (M==1) {
           possible = 1;
           for (j=0; j<N && possible; j++) {
                  possible = board[0][j] == board[0][j%4];
           }
           if (possible) printf("YES\n");
           else printf("NO\n");
           
        } else {
               
           if (N==1) {       
              possible = 1;
              for (i=0; i<M && possible; i++) {
                     possible = board[i][0] == board[i%4][0];
              }
              if (possible) printf("YES\n");
              else printf("NO\n");
           }
        }
        
        if (M>1 && N>1) {
            /*
                 M=0, I=1, H=4, N=2, Qu=8, U=3
                 4
                 0 2 8 1
                 3
            */
                
            die[0] = board[0][0];
            
            possible = 0;
            for (p=0; p<2 && !possible; p++) {
    
                if (p==0) die[3] = board[0][1];
                else die[4] = board[1][0];
                
                for (c=0; c<colcount*colcount*colcount*colcount && !possible; c++) {            
                    // set colors represented by s to the die sides
                    cc = c;
                    for (i=1; i<6; i++) {
                        if ((p==0 && i==3) || (p==1 && i==4)) {
                           i++;
                        }
                        die[i] = col[cc%colcount];
                        cc /= colcount;    
                    }
                    
                    /*
                    die[1] = 2; // die for sample input
                    die[2] = 8;
                    die[4] = 4;
                    die[5] = 3;
                    */
                    
                    // for (i=0; i<6; i++) printf("%d ",die[i]);
                    // printf("<- current die\n"); 
                    
                    // init seen
                    for (i=0; i<M; i++) {
                        for (j=0; j<N; j++) {
                            for (s=0; s<6; s++) {
                                for (u=0; u<6; u++) {
                                    seen[i][j][s][u] = 0;
                                }
                            }
                        }
                    }
        
                    // try this die
                    dd.cs = 0;
                    dd.u = 4;
                    dd.d = 5;
                    dd.l = 3;
                    dd.r = 1;
                    dd.b = 2;
                    possible = roll(0,0,dd);
                    
                    // printf("possible = %d\n",possible);
                    // return 2;
                    
                    // char sss[100];
                    // scanf("%s",sss);
                }
            }
            
            if (possible) printf("YES\n");
            else printf("NO\n");
        }
    }
    
    return 0;   
}
