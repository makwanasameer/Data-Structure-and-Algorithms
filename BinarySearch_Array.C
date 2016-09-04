/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
Objective:program to implement binary search:
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void main()
{
	int a[20],n,i,g,x;
	int p,q;
	int binary_search(int a[],int n,int x,int p,int q);
	clrscr();
	printf("How many elements do you want to enter:?\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter the %d element:: ",i+1);
		scanf("%d",&a[i]);
	}
	printf("Enter the element to search:\n");
	scanf("%d",&x);
	p=0;
	q=n-1;
	g=binary_search(a,n,x,p,q);
	if(g==0)
	{
		printf("unsuccessful search:\n");
	}
	else
	{
		printf("The index is as follows :: %d",g+1);
}       }
int binary_search(int a[],int n,int x,int p,int q)
{
	int loc,middle;
	if(a[p]>a[q])
	{
		loc=0;
		exit(1);
	}
	middle=((p+q)/2);
	if(x<a[middle])
	{
		loc=binary_search(a,n,x,p,middle-1);
	}
	else
	if(x>a[middle])
	{
		loc=binary_search(a,n,x,middle+1,q);
	}
	else
	{
		loc=middle;
	}
	return(loc);
};
/*
How many elements do you want to enter:?
5
1
2
3
4
5
Enter the element to search:
5
The index is as follows :: 5
*/


                                                                                
                                                                                

                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                



