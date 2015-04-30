#include <stdio.h>
#include <stdlib.h>

int k,ik,m,n,caso;

#define MT 2000

#define QUELE 1000000

// 0 = top
// 1 = north
// 2 = east
// 3 = south
// 4 = west
// 5 = bottom

int A[300][300];

char B[300][300][MT+1][6];
int C[300][300];

int ST[QUELE][8],STR,STW;

int GOOD;

int b0,b1,b2,b3,b4,b5,nx,ny,i,OK,SUP,j,mt,x,y,a0,a1,a2,a3,a4,a5;



int main() {
		scanf("%d %d ",&m,&n);
		
		//printf("DBG: %d %d %d\n",ik,m,n);

		for (i=0;i<m;i++) {
			for (j=0;j<n;j++) {
				scanf("%d ",&(A[i][j]));
				A[i][j]++;
				C[i][j]=0;
			}
		}
		
		//printf("DBG2: %d %d %d\n",ik,m,n);
		
		STW=1; STR=0; 
		ST[0][0]=0; ST[0][1]=0; ST[0][2]=A[0][0]; ST[0][3]=0; ST[0][4]=0; ST[0][5]=0; ST[0][6]=0; ST[0][7]=0; 
		
		GOOD=0;
		
        while (STR!=STW) {
	   	  y=ST[STR][0]; x=ST[STR][1]; a0=ST[STR][2]; a1=ST[STR][3]; a2=ST[STR][4]; a3=ST[STR][5]; a4=ST[STR][6]; a5=ST[STR][7]; 
	   	  STR=(STR+1)%QUELE;
	
    	  //printf("[%d %d]",y,x); fflush(NULL);
	
          if ((y==m-1)&&(x==n-1)) {                             
            //printf("\nDBG: [T:%d N:%d E:%d S:%d W:%d B:%d]\n",a0,a1,a2,a3,a4,a5); 
            GOOD=1;     
   	        goto DONE;
          }
                 
	      // roll-up 
   	      b0=a3; b1=a0; b3=a5; b5=a1; b2=a2; b4=a4; nx=x; ny=y-1;
  	      //-----------------------------------------------------------
	      if ( (y)&&( (A[ny][nx]==b0)||(b0==0)) )  {
		    b0=A[ny][nx];
		
		    mt=C[ny][nx]; 
		    B[ny][nx][mt][0]=b0; B[ny][nx][mt][1]=b1; B[ny][nx][mt][2]=b2;
		    B[ny][nx][mt][3]=b3; B[ny][nx][mt][4]=b4; B[ny][nx][mt][5]=b5;
				
		    OK=1; 
	        for (i=0;i<mt;i++) {
	    	
	    	  SUP=1;
	    	  for (j=0;j<6;j++) {
	    		// B[ny][nx][i][ * ]   vs B[ny][nx][mt][ * ] ... if it is forcing and I am different => I am new
	    		if ((B[ny][nx][i][j])&&(B[ny][nx][i][j]!=B[ny][nx][mt][j])) SUP=0;
	    	  }
	    	  if (SUP) OK=0;
	        }
	    
	        if (OK) {
	    	  C[ny][nx]++; if (C[ny][nx]>=MT) { printf("ERROR BOUNDS\n"); exit(-1); }
	    	  //explore(ny,nx,b0,b1,b2,b3,b4,b5);
  			  ST[STW][0]=ny; ST[STW][1]=nx; ST[STW][2]=b0; ST[STW][3]=b1; ST[STW][4]=b2; ST[STW][5]=b3; ST[STW][6]=b4; ST[STW][7]=b5; 
  			  STW=(STW+1)%QUELE; if (STW==STR) { printf("QUEUE OVERFLOW\n"); exit(-1); }
            }    
          }
	
	      // roll-down
   	      b3=a0; b0=a1; b5=a3; b1=a5; b2=a2; b4=a4; nx=x; ny=y+1;
	      //-----------------------------------------------------------
	      if ( (y<m-1)&&( (A[ny][nx]==b0)||(b0==0)) )  {
		     b0=A[ny][nx];
		
		     mt=C[ny][nx]; 
		     B[ny][nx][mt][0]=b0; B[ny][nx][mt][1]=b1; B[ny][nx][mt][2]=b2;
		     B[ny][nx][mt][3]=b3; B[ny][nx][mt][4]=b4; B[ny][nx][mt][5]=b5;
				
		     OK=1; 
	         for (i=0;i<mt;i++) {
	    	
 	           SUP=1;
	    	   for (j=0;j<6;j++) {
	    		 // B[ny][nx][i][ * ]   vs B[ny][nx][mt][ * ] ... if it is forcing and I am different => I am new
	    		 if ((B[ny][nx][i][j])&&(B[ny][nx][i][j]!=B[ny][nx][mt][j])) SUP=0;
	    	   }
	    	   if (SUP) OK=0;
	         }
	    
	         if (OK) {
	    	   C[ny][nx]++; if (C[ny][nx]>=MT) { printf("ERROR BOUNDS\n"); exit(-1); }
	    	   //explore(ny,nx,b0,b1,b2,b3,b4,b5);
  			   ST[STW][0]=ny; ST[STW][1]=nx; ST[STW][2]=b0; ST[STW][3]=b1; ST[STW][4]=b2; ST[STW][5]=b3; ST[STW][6]=b4; ST[STW][7]=b5; 
  			   STW=(STW+1)%QUELE; if (STW==STR) { printf("QUEUE OVERFLOW\n"); exit(-1); }
             }
           }
           	
	       // roll-left
	       b4=a0; b0=a2; b2=a5; b5=a4; b1=a1; b3=a3; nx=x-1; ny=y;
	       //-----------------------------------------------------------
	       if ( (x)&&( (A[ny][nx]==b0)||(b0==0)) )  {
		      b0=A[ny][nx];
		
		      mt=C[ny][nx]; 
		      B[ny][nx][mt][0]=b0; B[ny][nx][mt][1]=b1; B[ny][nx][mt][2]=b2;
		      B[ny][nx][mt][3]=b3; B[ny][nx][mt][4]=b4; B[ny][nx][mt][5]=b5;
				
		      OK=1; 
              for (i=0;i<mt;i++) {
	    	
                SUP=1;
	    	    for (j=0;j<6;j++) {
	    		  // B[ny][nx][i][ * ]   vs B[ny][nx][mt][ * ] ... if it is forcing and I am different => I am new
	    		  if ((B[ny][nx][i][j])&&(B[ny][nx][i][j]!=B[ny][nx][mt][j])) SUP=0;
	    	    }
	    	    if (SUP) OK=0;
	          }
	    
	          if (OK) {
                C[ny][nx]++; if (C[ny][nx]>=MT) { printf("ERROR BOUNDS\n"); exit(-1); }
	    	    //explore(ny,nx,b0,b1,b2,b3,b4,b5);
   			    ST[STW][0]=ny; ST[STW][1]=nx; ST[STW][2]=b0; ST[STW][3]=b1; ST[STW][4]=b2; ST[STW][5]=b3; ST[STW][6]=b4; ST[STW][7]=b5; 
   			    STW=(STW+1)%QUELE; if (STW==STR) { printf("QUEUE OVERFLOW\n"); exit(-1); }	             
              }
            }
	
	        // roll-right
	        b0=a4; b2=a0; b5=a2; b4=a5; b1=a1; b3=a3; nx=x+1; ny=y;
	        //-----------------------------------------------------------
	        if ( (x<n-1)&&( (A[ny][nx]==b0)||(b0==0)) )  {
		      b0=A[ny][nx];
		
		      mt=C[ny][nx]; 
		      B[ny][nx][mt][0]=b0; B[ny][nx][mt][1]=b1; B[ny][nx][mt][2]=b2;
		      B[ny][nx][mt][3]=b3; B[ny][nx][mt][4]=b4; B[ny][nx][mt][5]=b5;
				
		      OK=1; 
	          for (i=0;i<mt;i++) {
	    	
	    	    SUP=1;
	    	    for (j=0;j<6;j++) {
	    		  // B[ny][nx][i][ * ]   vs B[ny][nx][mt][ * ] ... if it is forcing and I am different => I am new
	    		  if ((B[ny][nx][i][j])&&(B[ny][nx][i][j]!=B[ny][nx][mt][j])) SUP=0;
	      	    }
	    	    if (SUP) OK=0;
	          }
	    
	          if (OK) {
	    	    C[ny][nx]++; if (C[ny][nx]>=MT) { printf("ERROR BOUNDS\n"); exit(-1); }
	    	    //explore(ny,nx,b0,b1,b2,b3,b4,b5);
   			    ST[STW][0]=ny; ST[STW][1]=nx; ST[STW][2]=b0; ST[STW][3]=b1; ST[STW][4]=b2; ST[STW][5]=b3; ST[STW][6]=b4; ST[STW][7]=b5; 
   			    STW=(STW+1)%QUELE; if (STW==STR) { printf("QUEUE OVERFLOW\n"); exit(-1); }	
              }
            }
          }
	
// -----------------------------------------------------------------------------------------	    
		
DONE:		

		if (GOOD) printf("YES\n"); else printf("NO\n");
				
		/*
		for (i=0;i<m;i++) {
			for (j=0;j<n;j++) {
				printf("%d ",A[i][j]);
			}
			printf("\n");
		}
		*/
		
		
		
		
}
