/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
Objective:-to implement the circular linked list
*/

#include<stdio.h>
#include<conio.h>
#include<alloc.h>
#include<stdlib.h>
struct node
{
	int num;
	struct node *next;
}*start,*last;
typedef struct node node;

node *insertfirst(node *start)
{
	node *p;
	p=(node *)malloc(sizeof(node));
	printf("\tEnter the number:\n");
	scanf("%d",&p->num);
	if(start==NULL)
	{
		p->next=p;
		start=p;
		last=p;
	}
	else
	{
		p->next=start;
		start=p;
		last->next=p;
	}
	return(start);
};
node *insertlast(node *start)
{       node *p;
	p=(node *)malloc(sizeof(node));
	printf("\t\tEnter the number:\n");
	scanf("%d",&p->num);
	if(start==NULL)
	{
		p->next=p;
		start=last=p;
	}
	else
	{
		last->next=p;
		last=p;
		last->next=start;
	}
	return(start);
}
node *deletefirst(node *start)
{
	node *p;
	p=start;
	if(p==NULL)
	{
		printf("\t\t List is empty:\n");
	}
	else
	{
		p=start;
		start=start->next;
		printf("\t\t Element deleted is %d",p->num);
		last->next=p;
	}
	return(start);
}
node *deletelast(node *start)
{
	node *p,*q;
	p=start;
	if(p==NULL)
	{
		printf("\t\t List is empty:");
	}
	else
	{
		while(p->next!=last)
		{
			q=p;
			p=p->next;
		}
		printf("\t\t Element deleted is %d",p->num);
		q->next=p->next;
	}
	last=q;
	return(start);
}
void traverse(void)
{
	node *p;
	p=start;
	if(p==NULL)
	{
		printf("\t\tLIst is empty:\n");
	}
	else
	{
                do
		{
			printf("\n\n\t\tNumber=%d\n",p->num);
			p=p->next;

		}	while((p->next)!=last->next);
		printf("\n\n\t\tNumber=%d\n",p->num);
	}
};


void main()
{
	int choice;
	node *insertfirst(node *);
	node *insertlast(node *);
	node *deletefirst(node *);
	node *deletelast(node *);
	start=NULL;
     	last=NULL;
	do
	{
		clrscr();
		printf("\t\t\t 1.Insert at the beginning:\n");
		printf("\t\t\t 2.Insert at the end:\n");
		printf("\t\t\t 3.Delete at the beginning:\n");
		printf("\t\t\t 4.Delete at the end:\n");
		printf("\t\t\t 5.Traverse:\n");
		printf("\t\t\t 6.exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:start=insertfirst(start);
				break;
			case 2:start=insertlast(start);
				break;
			case 3:start=deletefirst(start);
				getch();
				break;
			case 4:start=deletelast(start);
				getch();
				break;
			case 5:traverse();
				getch();
				break;
			case 6:exit(0);
		}
	}while(choice!=6);
}
