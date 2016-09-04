
#include<iostream.h>
#include<conio.h>
#include<process.h>
void create(int a[], int n)
{
	int q=0,i,j,k,temp;
	for(q=1;q<=n;q++)
	{
		i=q;
		k=a[q];
		j=(i/2);
		while(i>0 && k>a[j])
		{
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
			i=j;
			j=(i/2);
			if(j<0)
			{
				j=0;
			}
		}
		a[i]=k;
	}
}
void sort(int a[], int n)
{
	int q,temp,i,j,k;
	create(a,n);
	for(q=n;q>=1;q--)
	{
		temp=a[0];
		a[0]=a[q];
		a[q]=temp;
		i=0;
		k=a[0];
		j=1;
		if((j+1)<q)
		{
			if(a[j+1]>a[j])
			{
				j=j+1;
			}
		}
		while(j<=q-1 && a[j]>k)
		{
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
			i=j;
			j=2*i;
			if((j+1)<q)
			{
				if(a[j+1]>a[j])
				{
					j=j+1;
				}
				else if(j>n)
				{
					j=n;
				}
			}
			a[i]=k;
		}
	}
}
void display(int a[], int n)
{
	cout<<"\n Sorted list:";
	for(int i=0;i<n;i++)
	{
		cout<<"\n No:"<<a[i];
	}
}
void main()
{
	clrscr();
	int n,a[20];
	cout<<"\n Enter no of elements you want to enter:";
	cin>>n;
	cout<<"\n Enter list:";
	for(int i=0;i<n;i++)
	{
		cout<<"\n Enter no:";
		cin>>a[i];
	}
	cout<<"\n Original list:";
	for(int j=0;j<n;j++)
	{
		cout<<"\n No:"<<a[j];
	}
	sort(a,n);
	display(a,n);
	getch();
}

                          
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                









