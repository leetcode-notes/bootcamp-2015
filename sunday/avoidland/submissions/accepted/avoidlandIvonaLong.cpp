#include <stdio.h>
#define MAX 10000005

long row[MAX];
long col[MAX];
long N;

void printarray(long *a) {
     long i;
     for (i=1; i<=N; i++) printf("%ld ",a[i]);
     printf("\n");
}   

long shift(long *a) {
    long i,moves,j,m;
 
    moves = 0;
    i = 1; // current element
    for (j=1; j<=N && a[j]==0; j++); // nearest non-zero element after (or equal to) i
    
    while (i<=N) {

        // printf("i,j = %ld %d\n",i,j);
        // printarray(a);   

        if (a[i] > 0) {
           moves += a[i]-1; // need to move this many to the right
           a[i+1] += a[i]-1;
           a[i] = 1;
           i++;
           j++;

        } else {
         
           m = j-i; // this many items need to be moved to the left
           if (a[j] < m) m = a[j]; // only this many can move now
           a[j] -= m;
          
           while (m > 0) {
                moves += j-i; // to move the item from j to i
                m--;
                a[i] = 1;
                i++;
           }
        }
        
        // update j
        while (a[j] == 0) j++; // should not be problems with out of bounds since there must be a non-zero element
    }
    
    // printf("moves = %ld\n",moves);
    
    return moves;    
}

int main() {
    long k,i,r,c;

          scanf("%ld",&N);
          for (i=1; i<=N; i++) {
              row[i] = 0;
              col[i] = 0;    
          }
          
          for (i=1; i<=N; i++) {
              scanf("%ld %ld",&r,&c);    
              row[r]++;
              col[c]++;
          }      
          
          printf("%ld\n",shift(row)+shift(col));
    
    return 0;    
}
