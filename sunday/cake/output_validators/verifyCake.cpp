#include <stdio.h>
#include <stdlib.h>
#define MAX 10000005
#define MAXD 40005

int A,B,N;
char cake[MAXD][MAXD];

int main (int argc, char** argv) {
    // assuming first: original input
    //          second: the output
    
    FILE *fin, *fout;
    
    int k,i,j,p,remarea,foundrose,r1,r2,c1,c2,r,c,K;
    
    fin = fopen(argv[1],"rt");
    fout = fopen(argv[2],"rt");
    
    fscanf(fin,"%d",&K);
    for (k=1; k<=K; k++) {
        fscanf(fin,"%d %d %d",&A,&B,&N);
        for (i=1; i<=A; i++) {
            for (j=1; j<=B; j++) {
                cake[i][j] = 0;    
            }    
        }

        for (p=0; p<N; p++) {
            fscanf(fin,"%d %d",&r,&c);
            cake[r][c] = 1; // rose
        }
        
        remarea = A*B;
        for (p=0; p<N; p++) {
            if (fscanf(fout,"%d %d %d %d",&r1,&c1,&r2,&c2) != 4) {
               printf("rectangle expected -- not seen\n");
               return 2;
            }
            if (!(1<=r1 && r1<=r2 && r2<=A && 1<= c1 && c1<=c2 && c2<=B)) {
               printf("problem with rectangle description -- incorrect corners\n");
               return 3;            
            }
            foundrose = 0;
            for (i=r1; i<=r2; i++) {
                for (j=c1; j<=c2; j++) {
                    if (cake[i][j] == 1) foundrose = 1;
                    if (cake[i][j] == 2) {
                       printf("rectangles overlapping\n");               
                       return 4;
                    }
                    cake[i][j] = 2;    
                }    
            }
            if (!foundrose) {
               printf("rectangle does not contain a rose\n");                
               return 5;
            }
            remarea -= (r2-r1+1)*(c2-c1+1);
        }
        
        fscanf(fout,"%d",&i);
        if (remarea != 0 || i!=0) {
           printf("incorrect remarea -- possible to have 0\n");
           return 6;            
        }
        printf("Output %d/%d: OK!\n",k,K);
    }
    
    printf("OK!\n");
    
    return 0;   
}
