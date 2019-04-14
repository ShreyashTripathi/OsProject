#include<unistd.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
  int cur,n,reqArr[50];
  printf("Enter the current position: ");
  scanf("%d",&cur);
  printf("Enter the number of requests: ");
  scanf("%d",&n);
  printf("Enter the request order (FIFO): \n");
  for(int i=0;i<n;i++)
  {
     scanf("%d",&reqArr[i]);
  }
  int smaller[n],larger[n],x = 0,y = 0;
  for(int i = 0;i<n;i++)
  {
    if(reqArr[i] < cur)
    {
       smaller[x] = reqArr[i];
       x++;
    }
    else
    {
       larger[y] = reqArr[i];
       y++;
    }
  }
  //sorting the smaller array in descending order(Bubble Sort used here)
  int temp;
 
  for(int i=0;i<x;i++)
  {
    for(int j=0;j<x-1;j++)
    {
      if(smaller[j] < smaller[j+1])
      {
         temp = smaller[j];
         smaller[j] = smaller[j+1];
         smaller[j+1] = temp;
      }
    }
  }
 
  //sort the larger array in ascending order (Bubble sort used here also)
  for(int i=0;i<y;i++)
  {
    for(int j=0;j<y-1;j++)
    {
      if(larger[j+1] < larger[j])
      {
         temp = larger[j];
         larger[j] = larger[j+1];
         larger[j+1] = temp;
      }
    }
  }
  int prev,arr[n],z = 0;
  printf("Enter the previous position: ");
  scanf("%d",&prev);
  if((cur - prev) > 0 )
  {
    for(int i =0 ;i<y;i++)
    {
       arr[z] = larger[i];
       z++;
    }
    for(int i =0;i<x;i++)
    {
       arr[z] = smaller[i];
       z++;
    }
  }
  else
  {
   for(int i =0 ;i<x;i++)
    {
       arr[z] = smaller[i];
       z++;
    }
    for(int i =0;i<y;i++)
    {
       arr[z] = larger[i];
       z++;
    } 
  }
  int mov = 0;
  mov = abs(cur - arr[0]);
  printf("%d --> %d",cur,arr[0]);
    for(int i=1;i<z;i++)
    {
        mov=mov+abs(arr[i]-arr[i-1]);
        printf(" --> %d",arr[i]);
    }
  printf("\nTotal distance covered by disk arm: %d",mov);

}
