 /***********************************************************************
	
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
Objective : Polynomial
	
 *********************************************************************/

	 #include<stdio.h>
	 #include<conio.h>
	 #include<process.h>
	 #include<malloc.h>

	 struct node
	 {
		int co,nx,ny,nz;
		struct node *link;
	 };

	 void display(struct node *poly)
	 {
		while(poly!=NULL)
		{
			printf(" %dx%dy%dz%d +",poly->co,poly->nx,poly->ny,poly->nz);
			poly=poly->link;
		}
		printf("\b ");
		getch();
	 }

	 struct node *last1=NULL;
	 struct node *last2=NULL;
	 struct node *last3=NULL;

	 struct node * polylast(int x,int y,int z,int co,struct node *poly)
	 {
		 struct node *temp;
		 temp=(struct node *)malloc(sizeof(struct node));
		 temp->nx=x;
		 temp->ny=y;
		 temp->nz=z;
		 temp->co=co;
		 temp->link=NULL;
		 if(!poly)
		 {
			last3=temp;
			poly=temp;
			return(poly);
		 }
		 last3->link=temp;
		 last3=temp;
		 return(poly);
	 }


	 struct node * polyinsert(int x,int y,int z,int co,struct node *poly)
	 {
		struct node *temp;
		struct node *temp2;
		int a,b,c;
		temp=(struct node *)malloc(sizeof(struct node));
		temp2=(struct node *)malloc(sizeof(struct node));
		temp->nx=x;
		temp->ny=y;
		temp->nz=z;
		temp->co=co;
		if(!poly)
		{
			temp->link=NULL;
			poly=temp;
			return(poly);
		}
		a=poly->nx;
		b=poly->ny;
		c=poly->nz;
		if((x>a)||((x==a)&&(y>b))||((x==a)&&(y==b)&&(z>c)))
		{
			temp->link=poly;
			return(temp);
		}
		temp2=poly;
		while(temp2->link!=NULL)
		{
			a=(temp2->link)->nx;
			b=(temp2->link)->ny;
			c=(temp2->link)->nz;
			if((x<a)||((x==a)&&(y<b))||((x==a)&&(y==b)&&(z<c)))
			{
				temp2=temp2->link;
			}
			else
				break;
		}
		temp->link=temp2->link;
		temp2->link=temp;
		return(poly);
	 }

	 struct node * polyadd(struct node *poly1,struct node *poly2)
	 {
		struct node *poly3=NULL;
		int a1,a2,b1,b2,c1,c2,d1,d2;
		while(poly1!=NULL && poly2!=NULL)
		{
			a1=poly1->nx;
			a2=poly2->nx;
			b1=poly1->ny;
			b2=poly2->ny;
			c1=poly1->nz;
			c2=poly2->nz;
			d1=poly1->co;
			d2=poly2->co;
			if((a1==a2)&&(b1==b2)&&(c1==c2))
			{
				if((d1+d2)!=0)
			{
				poly3=polylast(a1,b1,c1,d1+d2,poly3);
				poly1=poly1->link;
				poly2=poly2->link;
			}
		}
		else if((a1>a2)||((a1==a2)&&(b1>b2))||((a1==a2)&&(b1==b2)&&(c1>c2)))
		{
			poly3=polylast(a1,b1,c1,d1,poly3);
			poly1=poly1->link;
		}
		else

		{
			poly3=polylast(a2,b2,c2,d2,poly3);
			poly2=poly2->link;
		}
	}
		if(poly1!=NULL)
			last3->link=poly1;
		else if(poly2!=NULL)
			last3->link=poly2;
		return(poly3);
	 }

	 void polynomial(void)
	 {
		struct node *poly1=NULL;
		struct node *poly2=NULL;
		struct node *poly3=NULL;
		int co,x,y,z;
		printf("\nEnter power of x:");
		scanf("%d",&x);
		printf("\nEnter power of y:");
		scanf("%d",&y);
		printf("\nEnter power of z:");
		scanf("%d",&z);
		printf("\nEnter coefficint:");
		scanf("%d",&co);
		while(co!=0)
		{
			poly1=polyinsert(x,y,z,co,poly1);
			printf("\nEnter power of x:");
			scanf("%d",&x);
			printf("\nEnter power of y:");
			scanf("%d",&y);
			printf("\nEnter power of z:");
			scanf("%d",&z);
			printf("\nEnter coefficint:");
			scanf("%d",&co);
		}
		printf("\n");
		display(poly1);
		getch();
		printf("\nEnter power of x:");
		scanf("%d",&x);
		printf("\nEnter power of y:");
		scanf("%d",&y);
		printf("\nEnter power of z:");
		scanf("%d",&z);
		printf("\nEnter coefficint:");
		scanf("%d",&co);
		while(co!=0)
		{
			poly2=polyinsert(x,y,z,co,poly2);
			printf("\nEnter power of x:");
			scanf("%d",&x);
			printf("\nEnter power of y:");
			scanf("%d",&y);
			printf("\nEnter power of z:");
			scanf("%d",&z);
			printf("\nEnter coefficint:");
			scanf("%d",&co);
		}
		printf("\n");
		display(poly2);
		getch();
	      //	display(poly1);
	      //	getch();
		poly3=polyadd(poly1,poly2);
		printf("\nSum is...\n");
		printf("==>");
		display(poly3);
		getch();
		return;
	 }

	 void main()
	 {
		clrscr();
		polynomial();
		getch();
	 }
	 /*

	 Enter power of y:2

	 Enter power of z:3

	 Enter coefficint:1

	 Enter power of x:1

	 Enter power of y:2

	 Enter power of z:3

	 Enter coefficint:1

	 Enter power of x:0

	 Enter power of y:0

	 Enter power of z:0

	 Enter coefficint:0

	  1x1y2z3 + 1x1y2z3
	 Enter power of x:1

	 Enter power of y:2

	 Enter power of z:3

	 Enter coefficint:1

	 Enter power of x:1

	 Enter power of y:2

	 Enter power of z:3

	 Enter coefficint:1

	Enter power of x:0

	 Enter power of y:0

	 Enter power of z:0

	 Enter coefficint:0

	  1x1y2z3 + 1x1y2z3
	 Sum is...
	 ==> 2x1y2z3 + 2x1y2z3
	 */