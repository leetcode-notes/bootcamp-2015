#include <stdio.h>
#include <stdlib.h>
#define MAX 10000005

struct cell {
       int r,c;
};

int A,B,N;
struct cell ch[MAX]; 

int cmpfnc (const void *x, const void *y) {
    struct cell xx,yy;
    xx = *(struct cell*)x;
    yy = *(struct cell*)y;
    
    if (xx.r < yy.r) return -1;
    if (xx.r > yy.r) return 1;
    // equal rows:
    
    return (xx.c - yy.c);
}


int main () {
    int k,i,maxr,lastrow,lastcol;
    
        scanf("%d %d %d",&A,&B,&N);
        maxr = 0;
        for (i=0; i<N; i++) {
            scanf("%d %d",&ch[i].r,&ch[i].c);
            if (ch[i].r > maxr) maxr = ch[i].r;    
        }        
        
        for (i=0; i<N; i++) {
            if (ch[i].r == maxr) ch[i].r = A;    
        }        

        qsort(ch, N, sizeof(struct cell), cmpfnc);

        // printf("%d\n",N);

        lastrow = 1;
        lastcol = 1;
        for (i = 0; i<N; i++) {
              if (i<N) {
                 if (ch[i].r == ch[i+1].r) {
                    printf("%d %d %d %d\n",lastrow,lastcol,ch[i].r,ch[i].c);
                    lastcol = ch[i].c+1;
                 } else {
                    printf("%d %d %d %d\n",lastrow,lastcol,ch[i].r,B);
                    lastrow = ch[i].r+1;
                    lastcol = 1;       
                 }
              }
        }
        printf("\n0\n");
    
    return 0;   
}
