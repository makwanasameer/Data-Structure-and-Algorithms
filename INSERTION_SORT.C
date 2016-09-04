/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
OBJECTIVE:INSERTION SORT
*/

#include<stdio.h>
#include<conio.h>
void main()
{
	int n,a[10],i,k,j,temp;
	clrscr();
	printf("\tHow many elements do you want to enter:?\n");
	scanf("%d",&n);
	printf("\tEnter the  elements\n");
	for(i=0;i<n;i++)
	{
		printf("Enter the %d element:: \t ",i+1);
		scanf("%d",&a[i]);
		printf("\n");
	}
	for(k=1;k<=n-1;k++)
	{
		temp=a[k];
		j=k-1;
		while((temp<a[j])&&(j>=0))
		{
			a[j+1]=a[j];
			j=j-1;
		}
		a[j+1]=temp;
	}
	printf("The sorted elements are as follows:\n");
	for(i=0;i<n;i++)
	{
		printf("%d \t",a[i]);
	}
	getch();
}
/*OUTPUT
	How many elements do you want to enter:?
5
	Enter the  elements
Enter the 1 element::    3

Enter the 2 element::    2

Enter the 3 element::    4

Enter the 4 element::    5

Enter the 5 element::    1

The sorted elements are as follows:
1       2       3       4       5
*/









                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
