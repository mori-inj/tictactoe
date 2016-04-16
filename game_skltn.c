#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a[3][3];
int main(void)
{
	int i,j;
	int vld_inp;
	int row;
	char col;
	int turn = 0;
	while(turn<9)
	{
		system("clear");
		for(i=0; i<3; i++)
		{
			if(!i)
				printf("    A   B   C\n   --- --- --- \n");
			printf("%d |",i+1);
			for(j=0; j<3; j++)
				printf(" %c |",a[i][j]==1 ? 'O' : a[i][j]==0? ' ': 'X');
			printf("\n   --- --- --- \n");
		}

		if(turn%2==0)
		{
			vld_inp = 0;
			while(!vld_inp)
			{
				scanf("%d%c",&row,&col);
				if(a[row-1][col-65]==0)
				{
					a[row-1][col-65]=1;
					vld_inp = 1;
				}
				else
					printf("Wrong input!\n");
			}
			turn++;
		}

		else
		{
			vld_inp = 0;
			while(!vld_inp)
			{
				row = rand()%3;
				col = rand()%3;
				if(a[row][col]==0)
				{
					a[row][col]=2;
					vld_inp = 1;
				}
			}
			turn++;
		}
		
		system("clear");
		for(i=0; i<3; i++)
		{
			if(!i)
				printf("    A   B   C\n   --- --- --- \n");
			printf("%d |",i+1);
			for(j=0; j<3; j++)
				printf(" %c |",a[i][j]==1 ? 'O' : a[i][j]==0? ' ': 'X');
			printf("\n   --- --- --- \n");
		}

	}
	return 0;
}
