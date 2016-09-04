/*
Roll no:09bce026
Author: Sameer Makwana
Licence: GPLv3
*/

#include <stdio.h>

#define N 6                       /* number of vertices */
#define M 15                      /* number of edges in graph */

int U[N];

void makeset (int i);
int find (int i);
void merge (int p, int q);
int equal (int p, int q);
void initial (int n);
void test_univ (void);
void pause (void);                /* used mainly for test purposes */

int main()
{  int W[N][N] = {0,2,4,1,3,2,    /* weighted graph */
		  2,0,6,4,5,1,
		  4,6,0,4,2,1,
		  1,4,4,0,5,4,
		  3,5,2,5,0,6,
		  2,1,1,4,6,0};
   int E[M][3];                   /* complete set of edges */
   int F[N-1][3];                 /* set of edges in min. span. tree */
   int num_edges = 0;             /* num of edges in min. span. tree */
   int next_edge = 0;             /* next edge not yet considered */
   int weight = 0;                /* minimal spanning tree weight */
   int a, b, c, i, j, k;          /* counter/placeholder variables */

   k = 0;
   for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
	 if (j > i)
	 {  E[k][0] = i;          /* first vertex of edge */
	    E[k][1] = j;          /* second vertex of edge */
	    E[k][2] = W[i][j];    /* weight of edge */
	    k++;
	 }

   for (i = 0; i < M; i++)
   {  for (j = 0; j < 3; j++)
	 printf(" %3d", E[i][j]);
      printf("\n");
   }

   pause();


   for (i = M - 1; i > 0; i--)
      for (j = 0; j < i; j++)
	 if (E[j][2] > E[j+1][2])
	 {  a = E[j][0];
	    b = E[j][1];
	    c = E[j][2];
	    E[j][0] = E[j+1][0];
	    E[j][1] = E[j+1][1];
	    E[j][2] = E[j+1][2];
	    E[j+1][0] = a;
	    E[j+1][1] = b;
	    E[j+1][2] = c;
	 }

   for (i = 0; i < M; i++)
   {  for (j = 0; j < 3; j++)
	 printf(" %3d", E[i][j]);
      printf("\n");
   }

   initial (N);

   for (i = 0; i < N - 1; i++)
      for (j = 0; j < 3; j++)
	 F[i][j] = -1;            /* '-1' denotes 'empty' */

   test_univ();
   while (num_edges < N - 1)
   {  a = E[next_edge][0];
      b = E[next_edge][1];

      i = find(a);
      j = find(b);

      if (!equal(i, j))
      {  merge (i, j);
	 F[num_edges][0] = E[next_edge][0];
	 F[num_edges][1] = E[next_edge][1];
	 F[num_edges][2] = E[next_edge][2];
	 num_edges++;

	 test_univ();
      }

      next_edge++;
   }

   printf("\nMinimal Spanning Tree Edges:\n");
   printf("F = (");
   for (i = 0; i < N - 1; i++)
   {  printf("(V%d,V%d)", F[i][0], F[i][1]);
      if (i < N - 2)
	 printf(", ");
      weight = weight + F[i][2];
   }
   printf(")\n");
   printf("Minimal Spanning Tree Weight = %d\n", weight);

   return (0);
}

void makeset (int i)
{  U[i] = i;
}

int find (int i)
{  int j;

   j = i;
   while (U[j] != j)
      j = U[j];
   return (j);
}

void merge (int p, int q)
{  if (p < q)
      U[q] = p;
   else
      U[p] = q;
}

int equal (int p, int q)
{  if (p == q)
      return (1);
   else
      return (0);
}

void initial (int n)
{  int i;

   for (i = 0; i < n; i++)
      makeset(i);
}


void test_univ (void)
{  int i;

   printf("\nThe disjoint subsets are:\n");
   for (i = 0; i < N; i++)
      printf(" %3d", U[i]);
   printf("\n");
}

void pause (void)
{  int i;

   printf("Press ENTER to continue...\n");
   i = getchar();
}