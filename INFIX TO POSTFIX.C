
/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
Objective:-convert infix expression to the postfix expression
*/



		#include<stdio.h>
		#include<conio.h>
		# define max 10

		char st[max];
		int top=1;

		void push(char item)
		  {
			top++;
			st[top]=item;
		  }
		char pop(void)
		  {
			char ch;
			ch=st[top];
			top--;

			return (ch);
			}

			void main()
       {
			int i,j;
			char amp[20],ch,arr[20],temp;
			clrscr();
			printf("enter axprassion\n");
			printf("to brek press enter key\n");
			i=0;
			while((ch=getchar())!='\n')
		  {
			i++;
			amp[i]=ch;
		  }

			amp[0]='(';
			i++;
			amp[1]=')';
			i++;
			amp[i]='\n';
			printf("\n\n axprassion is:\n");
			i=0;
			for(;amp[i]<='\n';i++)
		 {
			printf("%c",amp[i]);
		  }
			j=0;
			for(j=0;amp[j]!='\n';j++)
		  {
			if(amp[i]=='(')
		  {
			push('(');
			continue;
		  }
			else
		  {
			if(amp[i]=='*'|| amp[i]=='/')
		  {
			temp =pop();
			if(temp=='/'|| temp=='*')
		  {
			arr[j]=temp;
			j++;
			push(amp[i]);
			continue;
		  }
			else
		  {
			push(temp);
			push(amp[i]);
			continue;
		  }
		  }
			else
		  {
			if(amp[i]=='/'|| amp[i]==' ')
		  {
			temp=pop();
			 if(temp=='/'||temp=='*'||temp=='/'||temp==' ')
		 {
			arr[j]=temp;
			j++;
			push(amp[i]);
			continue;
		  }
			else
		  {
			push(temp);
			push(amp[i]);
			continue;
		  }
		 }
		 else
		 {
			if(amp[i]=='j')
		  {
			for(;temp==pop()!='(';j++)
		   {
			arr[j]=temp;
		   }
			continue;
		  }
			else
		 {
			arr[j]=amp[i];
			j++;
			continue;
		 }
	     }
	    }
	   }
	  }
			 arr[j]=amp[i];
			 printf("\n your emp and infix");
			for(j=0;arr[j]!='n';j++)
		 {
			printf("%c",arr[j]);
		 }
			getch();
		 }
  /*       OUTPUT:enter the expression:
			a+b*c-d
		expressiion is abc*+d-  */


