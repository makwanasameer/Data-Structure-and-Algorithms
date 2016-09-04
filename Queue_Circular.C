/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
objective:to implement the CIRCULAR queue

*/
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define N 5
int Q[N],F=0,R=0;
int insert(void)
{       int x;
	if(R>=N)
		R=1;
	else
		R=R+1;
	if(F==R)
	{
		printf("Queue overflow:\n");
		return(0);
	}
	printf("Enter the element to enter:\n");
	scanf("%d",&x);
	Q[R]=x;
	if(F==0)
	{
		F=1;
	}
	return(0);
};
int del(void)
{       int p;
	if(F==0)
	{
		printf("List is empty:\n");
		exit(0);
	}
	p=(Q[F]);
	if(F==R)
	{
		F=1;
		R=1;
		return(p);
	}
	if(F>=N)
	{
		F=1;
	}
	else
	{
		F=F+1;
	}
	return(p);
};
void display(void)
{       int i;
	for(i=5;i>0;i--)
	{
		printf("The elements are %d\n",Q[i]);
	}
};


void main()
{
	int insert(void);
	int del(void);
	void display(void);
	int n,l,z;
	int m;
	clrscr();
	do
	{
	clrscr();
	printf("What do you wamt to do:?\n");
	printf("1.insert\n");
	printf("2.delete\n");
	printf("3.display\n");
	scanf("%d",&n);
	switch(n)
	{
		case 1: 

			insert();
			getch();
			break;
		case 2: z=del();
			printf("deleted element is %d\n",z);
			getch();
			break;
		case 3: display();
			break;
	}
		printf("Do you want to continue:?\n");
		printf("1.yes\n");
		printf("2.no\n");
		scanf("%d",&l);
	}while(l==1);

}
/*
What do you wamt to do:?
1.insert
2.delete
3.display
1
Enter the element to enter:
1
Do you want to continue:?
1.yes
2.no
1
What do you wamt to do:?
1.insert
2.delete                                                                        
3.display                                                                       
1                                                                               
Enter the element to enter:                                                     
2                                                                               
Do you want to continue:?                                                       
1.yes                                                                           
2.no                                                                            
2
What do you wamt to do:?
1.insert
2.delete
3.display
3
The elements are 0
The elements are 0
The elements are 0
The elements are 2
The elements are 1
Do you want to continue:?
1.yes
2.no
2
*/




















































































































