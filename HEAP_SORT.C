
/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
Objective:HEAP SORT
*/

#include<stdio.h>
#include<conio.h>
#include<math.h>
void main()
{
int q,n,i=1,j,key,k[50],temp;
clrscr();
printf("how many elements you want to enter.....");
scanf("%d",&n);

for(i=1;i<n;i++)
{

scanf("%d\t",&k[i]);
}


for(q=2;q<=n;q++)
{
i=q;
key=k[q];
j=(i/2);


	while(i>1&&key>k[j])
	{
	   temp=k[i];
	   k[i]=k[j];
	   k[j]=temp;
	   i=j;
	   j=(i/2);
	   if(j<1)
	   {
	   j=1;
	   }
	}
k[i]=key;

}
for(q=n;q>=2;q--)
{

temp=k[1];
k[1]=k[q];
k[q]=temp;

i=1;
key=k[1];
j=2;


if(j+1<q)
{

if(k[j+1]>k[j])
{
j++;
}

}

	while(j<=(q-1)&&k[j]>key)

	{
	temp=k[i];
	k[i]=k[j];
	k[j]=temp;

	i=j;
	j=2*i;
		if((j+1)<q)
		{
			if(k[j+1]>k[j])
			{
			j++;
			}
		}
			else if(j<n)
			 {
			j=n;
			}
			else
			{
			k[i]=key;
			}

	}
	k[i]=key;


}

printf("                    SHORTED ARRAY");
printf("\n\n\n\n\n");
for(i=1;i<=n;i++)
{
printf("%d  ",k[i]);
}
getch();

}
/*OUTPUT
how many elements you want to enter.....6
4
2
5
3
1
7
		    SHORTED ARRAY
  1  2  3  4  5   7
  */













                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                


