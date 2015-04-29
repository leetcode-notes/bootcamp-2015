#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000005

struct coor {
       int x,y;
};

struct coor point[MAXN];
int N; // number pieces in the bottom row

struct coor bl; // bottom left (i.e., min x, out of those, min y)
struct coor avg;

int side[MAXN];
int sn; // number of sides

int samedir(int i, int j, int k) {
    if (k > N) return 0;
    if (k == N) k = 0;
    
    int ux,uy,vx,vy;
    ux = point[i].x - point[j].x;
    uy = point[i].y - point[j].y;
    vx = point[i].x - point[k].x;
    vy = point[i].y - point[k].y;
    
    return (ux*vy == vx*uy); 
}

void computeSides() {
     int i,j,ii;
     j = 0; // current side
     i = 0; // current vertex
     while (i<N) {
         side[j] = 2; // adding vertices i and i+1
         ii = i+2;
         while (samedir(i,i+1,ii)) {
               side[j]++;
               ii++;      
         }
         i = ii-1;
         j++;
     }
     sn = j;
}

int cmpfnc(const void *a, const void *b) {
    struct coor aa,bb,bla,blb,blavg;
    int orient;
    aa = *(struct coor*)a;
    bb = *(struct coor*)b;
    
    if (aa.x == bb.x && aa.y == bb.y) return 0;    
    if (aa.x == bl.x && aa.y == bl.y) return -1;    
    if (bb.x == bl.x && bb.y == bl.y) return 1;
    
    // need to check angle of bl-a with bl-b
    bla.x = aa.x-bl.x;
    bla.y = aa.y-bl.y;
    blb.x = bb.x-bl.x;
    blb.y = bb.y-bl.y;
    
    orient = bla.x*blb.y - bla.y*blb.x;
    if (orient != 0) return orient;
    
    blavg.x = N*bl.x - avg.x;
    blavg.y = N*bl.y - avg.y;
    
    orient = blavg.x*blb.y - blavg.y*blb.x;
    if (orient < 0) {
       if (bla.x != blb.x) {
          return (bla.x-blb.x);           
       }
       return (bla.y-blb.y);                  
    }
    return (blb.x-bla.x);           
}


int main() {
    int k,i,count,rem,left,right,offset;
    
    scanf("%d",&k);
    for (; k>0; k--) {
        scanf("%d",&N);
        scanf("%d %d",&point[0].x,&point[0].y);
        bl.x = point[0].x;
        bl.y = point[0].y;
        avg.x = point[0].x;
        avg.y = point[0].y;
        for (i=1; i<N; i++) {
            scanf("%d %d",&point[i].x,&point[i].y);
            if (point[i].x < bl.x || (point[i].x==bl.x && point[i].y < bl.y)) {
               bl.x = point[i].x;
               bl.y = point[i].y;
            } 
            avg.x += point[i].x;
            avg.y += point[i].y;
        }

        qsort(point,N,sizeof(struct coor),cmpfnc);
        // for (i=0; i<N; i++) printf("(%d,%d),",point[i].x,point[i].y);
        // printf("\n");
        
        computeSides();
        // printf("sides = %d\n",sn);
        // for (i=0; i<sn; i++) printf("%d,",side[i]);
        // printf("\n");
        
        count = 0;
        
        // pass 1: eliminate all sides of >3 points
        for (i=0; i<sn; i++) {
            if (side[i] > 3) {
               count++;
               side[i] = 0;
               left = (sn+i-1)%sn;
               if (side[left]>0) side[left]--;            
               right = (i+1)%sn;
               if (side[right]>0) side[right]--;            
            }
        }

        // printf("after pass 1, count = %d:\n",count);
        // for (i=0; i<sn; i++) printf("%d,",side[i]);
        // printf("\n");
        
        // pass 2: eliminate sides of 3 points
        offset = 0;
        if (side[0] == 3) {
           // special case, might be that there are sides 3 before
           for (offset = sn-1; side[offset]==3 && offset>0; offset--);
           // if offset==0, all 3's -> ok to start with 0
        }
        // printf("offset = %d\n",offset);
        
        for (i=0; i<sn; i++) {
            if (side[(offset+i)%sn] == 3) {
               count++;
               side[(offset+i)%sn] = 0;
               left = (offset+sn+i-1)%sn;
               if (side[left]>0) side[left]--;            
               right = (offset+i+1)%sn;
               if (side[right]>0) side[right]--;            
            }
        }
        
        // printf("after pass 2, count = %d:\n",count);
        // for (i=0; i<sn; i++) printf("%d,",side[i]);
        // printf("\n");

        // pass 3: eliminate sides of 2 points
        for (i=0; i<sn; i++) {
            if (side[i] == 2) {
               count++;
               side[i] = 0;
               left = (sn+i-1)%sn;
               if (side[left]>0) side[left]--;            
               right = (i+1)%sn;
               if (side[right]>0) side[right]--;            
            }
        }
        
        // printf("after pass 3, count = %d:\n",count);
        // for (i=0; i<sn; i++) printf("%d,",side[i]);
        // printf("\n");

        // pass 4: pair up remaining points
        rem = 0;
        for (i=0; i<sn; i++) {
            // check for pair of consecutive 1's: if so, then only one point left
            if (side[i] > 0 && side[(i+1)%sn] == 0) {
               rem++;
            }
        }
        count += (rem+1)/2;
        
        // printf("after pass 4, count = %d:\n",count);
        
        printf("%d\n",count);
    }
    
    return 0;
}
