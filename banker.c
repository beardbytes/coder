#include<stdio.h>
#include<stdlib.h>


void accept(int m,int n,int avail[20],int temp[20],int max[20][20],int alloc[20][20],int need[20][20])
{
int i,j;

  printf("\n enter maximum instances available for each resource\n ");
  for(i=0;i<m;i++)
    {
    printf("Resource Type R%d  ",i);
    scanf("%d",&avail[i]);
    temp[i]=avail[i];
    }
    for(i=0;i<n;i++) 
    {
      printf("\nenter maximum claim for proces P%d ",i);
	for(j=0;j<m;j++)
	  {
	    printf("\nenter maximum claim for resource type R%d ",j);
	    scanf("%d",&max[i][j]);
	    if(max[i][j] > temp[j])
	      { printf(" error! Process cannot claim more than avilable!");
	       exit(0);
	      }
	  }
    }
    for(i=0;i<n;i++) 
    {
      printf("\nenter allocation of resources for proces P%d ",i);
	for(j=0;j<m;j++) 
	  {
	    printf("\nenter allocation for resource type R%d ",j);
	    scanf("%d",&alloc[i][j]);
	    need[i][j] = max[i][j]-alloc[i][j]; 
	    if (need[i][j] < 0) 
	     {                 
	       printf(" Error! cannot allocate more than required ");
	       exit(0);
	     }
	    avail[j] = avail[j]-alloc[i][j]; 
	    if (avail[j] < 0) 
	     {                
	       printf("Error! Insufficient no of resources remaining");
	       exit(0);
	     }
	  }
    }
clrscr();
}
void disp_vector(int v[20], int s)
{
int i;
   printf("\n");
    for(i=0;i<s;i++)
      printf("%4d", v[i]);
      printf("\n");
}
void disp_matrix(int mat[20][20], int m,int n)
{
int i,j;
for(i=0;i<n;i++)
    {
      printf("\n");
	for(j=0;j<m;j++)
	  {
	    printf("%3d",mat[i][j]);
	  }
    }
printf("\n");
}
int safety(int m,int n,int avail[20],int alloc[20][20],int need[20][20])
{
  int i,j,l,done,k;
  int finish[20],safeseq[20],work[20];
  l=0; done = 0; k=0;
    for(i=0;i<n;i++)
     finish[i] = 0;  
    for (i=0;i<m;i++)
     work[i] = avail[i]; 
    while( l < n && !done)   
      {
	 i = 0;
	   while(i < n && !done)   
	      {
		if(!finish[i])
		  {
		     for ( j=0; j<m;j++)   
		       if (need[i][j] > work[j]) break;
		      if ( j==m) 
			{
			 finish[i] = 1;  
			 safeseq[k] = i;  
			 k++;
			 for(j=0;j<m;j++)
			   work[j] = work[j] + alloc[i][j]; 
			 }
		  }
		  if(k==n) done = 1; 
		  i++;
	      }
	   l++;
	}
   if(done)
     {
       printf("\n safety sequence is  < ");
       for(i=0;i<n;i++)
	 printf("P%d ",safeseq[i]);
	 printf(" >");

     }
  else
     printf("\n system is not in the safe state");

     return(done);
}
void process_request(int m, int n,int avail[20], int alloc[20][20], int need[20][20])
{
 int i,j,k,is_safe;
 int request[20];
 printf("\n enter the process no requesting for resources ");
 scanf("%d",&k);
 printf("\n enter no of instances required for each resource type \n");
 for(j=0;j<m;j++)
   {
     printf("resource type R%d ",j);
     scanf("%d",&request[j]);    
     if (request[j] > need[k][j]) 
	{
	 printf(" request cannot be granted, request is more than need\n ");
	 return;
	}
     if (request[j] > avail[j]) 
	{
	 printf(" request cannot be granted, request is more than available ");
	 return;
	}
   }
  for(j=0; j<m;j++)
    {
      avail[j] = avail[j] - request[j];
      alloc[k][j] = alloc[k][j] + request[j];
      need[k][j] = need[k][j] - request[j];
    }
    printf("\n new state is printed,  wait...press a key to continue\n");getch();
    clrscr();
    printf("\n need matrix after allocation");
    disp_matrix(need,m,n);
    printf("\n allocation matrix after allocation");
    disp_matrix(alloc,m,n);
    printf("\n available resources after allocation");
    printf("\n   R0  R1  R2");
    disp_vector(avail,m);

    is_safe=safety(m,n,avail,alloc,need);
    if(is_safe)
	 printf("\n Request for the process has been granted");
    else
	{
	 printf("\n Request for the process cannot be granted");
	 printf("\n wait, system is restoring its safe state press a key to continue");
	 getch();
	 for(j=0; j<m;j++)
	  {
	    avail[j] = avail[j] + request[j];
	    alloc[k][j] = alloc[k][j] - request[j];
	    need[k][j] = need[k][j] + request[j];
	  }
	      clrscr();
	  printf("\n need matrix ");
	  disp_matrix(need,m,n);
	  printf("\n allocation matrix ");
	  disp_matrix(alloc,m,n);
	  printf("\n available resources");
	  printf("\n   R0  R1  R2");
	  disp_vector(avail,m);
	}
   }



int main()
{
int ans,is_safe,m,n;
int avail[20],temp[20], need[20][20],alloc[20][20],max[20][20];
    printf("enter no of processes ");
    scanf("%d",&n);
    printf("enter no of resource types ");
    scanf("%d",&m);
    accept(m,n,avail,temp,max,alloc,need);
    printf("\n available resources in the system");
    printf("\n   R0  R1  R2");
    disp_vector(temp,m);
    printf("\n maximum claim matrix");
    disp_matrix(max,m,n);
    printf("\n allocation matrix");
    disp_matrix(alloc,m,n);
    printf("\n need matrix");
    disp_matrix(need,m,n);
    printf("\n maximum available resources after allocation");
    printf("\n   R0  R1  R2");
    disp_vector(avail,m);
    is_safe = safety(m,n,avail,alloc,need); 
      if(is_safe)
	{
	 do
	 {
	  process_request(m,n,avail,alloc,need);
	  printf(" \n any more requests to be processed: 1 for yes ");
	  flushall();
	  scanf("%d",&ans);
	  if(ans!=1) break;
	  }
	 while(1);
	}
	return(0);
}


