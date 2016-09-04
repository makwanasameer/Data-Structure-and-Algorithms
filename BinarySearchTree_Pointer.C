/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
OBJECTIVE: BINARY SEARCH TREE
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node
{
	struct node *left;
	int num;
	struct node *right;
};
typedef struct node node;
node *P=NULL;
node *temp;
node *save;
void main()
{       int n,digit,g,o;
	node *insert(node *,int );
	void preorder(node *P);
	void inorder(node *P);
	void postorder(node *P);
	void deltree(void);
	do
	{
	printf("\tWhat do you want to do? \n");
	printf("\t\t 1) insert the element:\n");
	printf("\t\t 2) preorder traversal:\n");
	printf("\t\t 3) inorder traversal:\n");
	printf("\t\t 4) postorder traversal:\n");
	printf("\t\t 5) delete \n");
	scanf("%d",&n);
	switch(n)
	{
		case 1: printf("\tEnter the digit:\n");
			scanf("%d",&digit);
			while(digit!=0)
			{
				P=insert(P,digit);
				scanf("%d",&digit);
			}
			break;
		case 2: printf("\tThe preorder traversal is as follows:\n");
			preorder(P);
			getch();
			break;
		case 3: printf("\t The inorder traversal is as follows:\n");
			inorder(P);
			getch();
			break;
		case 4: printf("\t The postorder traversal is as follows:\n");
			postorder(P);
			getch();
			break;
		case 5: printf("\t delete\n");
			deltree();
			break;
	 }
		printf("\t DO you want to continue:\n");
		printf("\t 1)YES\n");
		printf("\t 2)NO\n");
		scanf("%d",&g);
		clrscr();

	 }while(g==1);
}
node *insert(node *P,int digit)
{
	if(P==NULL)
	{
		P=(node *)malloc(sizeof(node));
		P->left=P->right=NULL;
		P->num=digit;
	}
	else if(digit<P->num)
	{
		P->left=insert(P->left,digit);
	}
	else if(digit>P->num)
	{
		P->right=insert(P->right,digit);
	}
	else if(digit==P->num)
	{
		exit(0);
	}
	return(P);
};
void preorder(node *P)
{
	if(P!=NULL)
	{
		printf("%d\n",P->num);
		preorder(P->left);
		preorder(P->right);
	}
};
void inorder(node *P)
{
	if(P!=NULL)
	{
		inorder(P->left);
		printf("%d\n",P->num);
		inorder(P->right);
	}
};
void postorder(node *P)
{
	if(P!=NULL)
	{
		preorder(P->left);
		preorder(P->right);
		printf("%d",P->num);
	}
};

void deltree(void)
{
	int k,found=0;
	printf("Enter the element which u want to delete:\n");
	scanf("%d",&k);
	temp=P;
	while(found==0)
	{
		if(k<=temp->num)
		{
			if(k==temp->num)
			{
				found=1;
				break;
			}
			else
			{       save=temp;
				temp=temp->left;
			}
		}
		else
		{
			if(k==temp->num)
			{
				found=1;
				break;
			}
			else
			{       save=temp;
				temp=temp->right;
			}
		}
	}
	if(found==1)
	{
		if((save->num)<(temp->num))
		{
			if(temp->left==NULL&&temp->right==NULL)
			{
				temp=NULL;
			}
			if(temp->left==NULL)
			{
				save->left=temp->right;
			}
			if(temp->right==NULL)
			{
				save->left=temp->left;
			}
			if(temp->left!=NULL&&temp->right!=NULL)
			{
				save->left=temp->right;
			}
		else
		{
			if(temp->left==NULL&&temp->right==NULL)
			{
				temp=NULL;
			}
			if(temp->left==NULL)
			{
				save->right=temp->right;
			}
			if(temp->right==NULL)
			{
				save->right=temp->left;
			}
			if(temp->left!=NULL&&temp->right!=NULL)
			{
				save->right=temp->right;
			}
		}
	}
}
}






