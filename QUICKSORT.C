/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
OBJECTIVE:QUICK SORT
*/

#include<stdio.h>
#include<conio.h>
int n,i,l,h,a[20];
void main()
{
	void input(void);
        clrscr();
	input();
	getch();
}
void input(void)
{
	void quick_sort(int a[],int l,int h);
	void output(int a[],int n);
	printf("How many elements in the array:\n");
	scanf("%d",&n);
	printf("Enter the elements:\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	l=0;
	h=n-1;
	quick_sort(a,l,h);
	printf("sorted array:\n");
	output(a,n);
}
void quick_sort(int a[],int l,int h)
{
	int temp,key,low,high;


		low=l;
		high=h;
		key=a[(low+high)/2];

	

	do{
	//   low++;
		while(key>a[low])
		{
			low++;
		}
	     //	high--;
		while(key<a[high])
		{
			high--;
		}
		if(low<=high)
		{
			temp=a[low];
			a[low++]=a[high];
			a[high++]=temp;
		}


	}while(low<=high);
		if(l<high)
		quick_sort(a,l,high);
		if(low<h)
		quick_sort(a,low,h);

}
void output(int a[],int n)
{
	for(i=0;i<n;i++)
	{
		printf("\t\t%d\n",a[i]);
	}

}
/*
How many elements in the array:
5
Enter the elements:
4
3
2
1
5
sorted array:
		1
		2
		3
		4
		5

*/



                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                

