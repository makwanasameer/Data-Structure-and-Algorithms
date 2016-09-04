/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
OBJECTIVE:PRIORITY QUEUE
*/

#include<stdio.h>
#include<conio.h>
void main()
{
 int n,a[10],i,j,t,te;
 int p[10];
 clrscr();

 printf("ENTER HOW MANY NO U WANT TO ENTER: ");
 scanf("%d",&n);


 for(i=0;i<n;i++)
 {
     printf("ENTER THE A[%d] :",i);
     scanf("%d",&a[i]);
     printf("ENTER THE P[%d] :",i);
     scanf("%d",&p[i]);
     printf("\n");
 }
 for(i=0;i<=n-1;i++)
 {
   for(j=0;j<n-1;j++)
   {
      if(a[j]>a[j+1])
      {
       t=a[j];
       a[j]=a[j+1];
       a[j+1]=t;

       te=p[j];
       p[j]=p[j+1];
       p[j+1]=te;
      }
   }
 }
 printf("THE SORTED ARRAY IS:\n ");
 printf("A[ ]\tP[ ]\n");
 for(i=0;i<n;i++)
 {
   printf("%d \t %d\n",a[i],p[i]);
 }
 getch();
}
/* OUTPUT
ENTER HOW MANY NO U WANT TO ENTER: 5
ENTER THE A[0] :1
ENTER THE P[0] :2

ENTER THE A[1] :3
ENTER THE P[1] :2

ENTER THE A[2] :4
ENTER THE P[2] :1

ENTER THE A[3] :5
ENTER THE P[3] :2

ENTER THE A[4] :4
ENTER THE P[4] :1

THE SORTED ARRAY IS:
 A[ ]   P[ ]
1        2
3        2
4        1
4        1
5        2
*/







                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                



