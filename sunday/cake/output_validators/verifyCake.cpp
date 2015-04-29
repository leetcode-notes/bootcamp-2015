#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

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
    fout = stdin;
    string feedback_filename = string(argv[3])+"judgemessage.txt";
    FILE *feedback = fopen(feedback_filename.c_str(),"w");
    
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
               fprintf(feedback,"rectangle expected -- not seen\n");
               return 43;
            }
            if (!(1<=r1 && r1<=r2 && r2<=A && 1<= c1 && c1<=c2 && c2<=B)) {
               fprintf(feedback,"problem with rectangle description -- incorrect corners\n");
               return 43;            
            }
            foundrose = 0;
            for (i=r1; i<=r2; i++) {
                for (j=c1; j<=c2; j++) {
                    if (cake[i][j] == 1) foundrose = 1;
                    if (cake[i][j] == 2) {
                       fprintf(feedback,"rectangles overlapping\n");               
                       return 43;
                    }
                    cake[i][j] = 2;    
                }    
            }
            if (!foundrose) {
               fprintf(feedback,"rectangle does not contain a rose\n");                
               return 43;
            }
            remarea -= (r2-r1+1)*(c2-c1+1);
        }
        
        fscanf(fout,"%d",&i);
        if (remarea != 0 || i!=0) {
           fprintf(feedback,"incorrect remarea -- possible to have 0\n");
           return 43;            
        }
        fprintf(feedback,"Output %d/%d: OK!\n",k,K);
    }
    
    fprintf(feedback,"OK!\n");
    
    return 42;   
}
