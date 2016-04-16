#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define C 19683 //# of all possible cases
#define N 64 //# of individual life
#define GEN 16384 //generation
#define M 19683 // # of pivot (pivots are used to compare the winning rate of genes
#define MUT_RAT 2 // Mutant Rate * 100
#define K 8 //# of selected genes

int select[K];
int old_f[N][C],new_f[N][C];
int pivot[M][C];
int result[N],pivot_result[N];
int G[3][3];

void clear(void)
{
	system("clear");
}

int outcome(void)
{
	int i,j;
	int c[3]={};

	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			c[i]+= G[i][j]==1?1:G[i][j]==2?-1:0;

	for(i=0; i<3; i++)
	{
		if(c[i]==3)
			return 1;
		else if(c[i]==-3)
			return 2;
	}
	for(i=0; i<3; i++)
		c[i]=0;

	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			c[i]+= G[j][i]==1?1:G[j][i]==2?-1:0;


	for(i=0; i<3; i++)
	{
		if(c[i]==3)
			return 1;
		else if(c[i]==-3)
			return 2;
	}


	for(i=0; i<3; i++)
		c[i]=0;

	for(i=0; i<3; i++)
		c[0]+= G[i][i]==1?1:G[i][i]==2?-1:0;
	for(i=0; i<3; i++)
		c[1]+= G[i][2-i]==1?1:G[i][2-i]==2?-1:0;

	for(i=0; i<2; i++)
	{
		if(c[i]==3)
			return 1;
		else if(c[i]==-3)
			return 2;
	}


	return 0;
}

int game(int fst, int snd)
{
	int i,j;
	int cnt=0,c;
	int ret;



	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			G[i][j]=0;



	while(cnt<9)
	{
		c = 0;

		for(i=2; i>=0; i--)
			for(j=2; j>=0; j--)
			{
				c *= 3;
				c += G[i][j];
			}

		if(cnt%2)
			G[new_f[snd][c]/3][new_f[snd][c]%3]=2;
		else
			G[new_f[fst][c]/3][new_f[fst][c]%3]=1;
		cnt++;	


		ret = outcome();

		if(ret!=0)
			break;
	}

	return ret;
}

int pivot_game(int fst, int snd, int order)
{
	int i,j;
	int cnt,c;
	int ret;
	cnt = 0;
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			G[i][j]=0;

	while(cnt<9)
	{
		c = 0;

		for(i=2; i>=0; i--)
			for(j=2; j>=0; j--)
			{
				c *= 3;
				c += G[i][j];
			}

		if(order==0)
		{
			if(cnt%2==0)
				G[new_f[fst][c]/3][new_f[fst][c]%3]=1;
			else
				G[pivot[snd][c]/3][pivot[snd][c]%3]=2;
		}
		else
		{
			if(cnt%2==0)
				G[new_f[fst][c]/3][new_f[fst][c]%3]=2;
			else
				G[pivot[snd][c]/3][pivot[snd][c]%3]=1;

		}
		cnt++;	

		ret = outcome();
		if(ret!=0)
			break;
	}

	return ret;

}

int main(void)
{
	int i,j,k;
	int temp[3][3];
	int c,generation=0;
	int fst,snd,sel,sum,cnt,min,max;

	srand((unsigned)time(NULL));
	for(i=0; i<N; i++)
	{
		for(j=0; j<C; j++)
		{
			c = j;
			for(k=0; k<9; k++)
			{
				temp[k/3][k%3] = c%3;
				c /= 3;
			}

			c = 0;
			for(k=0; k<9; k++)
				if(temp[k/3][k%3]==0)
					c++;

			if(c==0)
				new_f[i][j]=-1;
			else
			{
				new_f[i][j] = rand()%9;
				while(temp[new_f[i][j]/3][new_f[i][j]%3]!=0)
					new_f[i][j] = rand()%9;
			}
		}
	}

	for(i=0; i<M; i++)
	{
		for(j=0; j<C; j++)
		{
			c = j;
			for(k=0; k<9; k++)
			{
				temp[k/3][k%3] = c%3;
				c /= 3;
			}

			c = 0;
			for(k=0; k<9; k++)
				if(temp[k/3][k%3]==0)
					c++;

			if(c==0)
				pivot[i][j]=-1;
			else
			{
				pivot[i][j] = rand()%9;
				while(temp[pivot[i][j]/3][pivot[i][j]%3]!=0)
					pivot[i][j] = rand()%9;
			}
		}
	}	


	printf("done\n");

	generation = 0;

	while(generation < GEN)
	{
		for(i=0; i<N; i++)
			result[i] = 0;
		for(i=0; i<N; i++)
		{
			for(j=0; j<M; j++)
			{
				int order = rand()%2;
				c = pivot_game(i,j,order);
				if((c==1 && order==0) || (c==2 && order==1))
					result[i]+=2;
				else if(c==0)
					result[i]+=0;
				else
					result[i]=-1;		
				
				
				/*fst = i;
				snd = j;

				c = game(fst,snd);

				if(c==1)
				{
					result[fst]+=2;
					result[snd]-=1;
				}
				else if(c==2)
				{
					result[fst]-=1;
					result[snd]+=2;
				}*/
				/*else
				{
					result[fst]++;
					result[snd]++;
				}*/
			}
		}	

		/*for(i=0; i<N; i++)
		  printf("%6d%c",result[i],(i+1)%10==0?'\n':0);
		  printf("\n");*/

		for(i=0; i<N; i++)
			for(j=0; j<C; j++)
				old_f[i][j]=new_f[i][j];

		int check[N]={};
		for(i=0; i<N; i++)
			check[i]=0;
		for(i=0; i<K; i++)
		{
			for(j=0; j<N; j++)
				if(check[j]==0)
				{
					select[i]=j;
					break;
				}

			for(j=1; j<N; j++)
			{
				if(result[j]>result[select[i]] && check[j]==0)
					select[i] = j;
			}
			check[select[i]]=1;
		}




		/*for(i=0; i<K; i++)
		{
			printf("%3d: ",select[i]);
			for(j=0; j<10; j++)
				printf("%4d   ",new_f[select[i]][j]);
			printf("\n");
		}*/


		/*for(i=0; i<K; i++)
			printf("%6d:%5d",select[i],result[select[i]]);
		printf("\n");*/


		for(i=0; i<N; i++)
		{
			fst = select[rand()%K];
			snd = select[rand()%K];
			//printf("%d: fst: %d %d snd: %d %d\n",i,fst,result[fst],snd,result[snd]);

			for(j=0; j<C; j++)
			{
				sel = rand() % 100;
				if(sel < rand() % MUT_RAT )
				{
					c = j;
					for(k=0; k<9; k++)
					{
						temp[k/3][k%3] = c%3;
						c /= 3;
					}

					c = 0;
					for(k=0; k<9; k++)
						if(temp[k/3][k%3]==0)
							c++;

					if(c==0)
						new_f[i][j]=-1;
					else
					{
						new_f[i][j] = rand()%9;
						while(temp[new_f[i][j]/3][new_f[i][j]%3]!=0)
							new_f[i][j] = rand()%9;
					}

				}				
				else if(sel%2==0)
				{
					new_f[i][j] = old_f[fst][j];
				}
				else
				{
					new_f[i][j] = old_f[snd][j];	
				}

			}
		}


		for(i=0; i<N; i++)
			pivot_result[i] = 0;
		for(i=0; i<N; i++)
			for(j=0; j<M; j++)
			{
				int order = rand()%2;
				c = pivot_game(i,j,order);
				if((c==1 && order==0) || (c==2 && order==1))
					pivot_result[i]++;
				else if(c==0)
					pivot_result[i]++;
				//else if((c==2 && order==0) || (c==1 && order==1))
				//	pivot_result[i]--;
			}

		sum = 0;
		min = M;
		max = 0;
		for(i=0; i<N; i++)
		{
			sum+=pivot_result[i];
			if(min>pivot_result[i])
				min = pivot_result[i];
			if(max<pivot_result[i])
				max = pivot_result[i];
		}

		printf("%dth: rate:%lf   min:%d max:%d sum:%d cnt:%d\n",generation,(double)sum/(double)N,min,max,sum,N);

		if((double)sum/(double)N > M-3)
			break;
		generation++;
	}

	sel = 0;
	for(i=1; i<N; i++)
		if(result[sel]<result[i])
			sel = i;


	FILE*fp = fopen("output.txt","r");

	for(i=0; i<N; i++)
	{
		for(j=0; j<C; j++)
			fprintf(fp,"%d ",new_f[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp);


	printf("selected: %d\n",i);






	printf("all done!!\n");

	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			G[i][j]=0;


	int turn = 0;
	int vld_inp;
	int row;
	char col;
	while(turn<9)
	{
		system("clear");
		for(i=0; i<15; i++)
			printf("%4d",new_f[sel][i]);
		printf("\n");
		for(i=0; i<3; i++)
		{
			if(!i)
				printf("    A   B   C\n   --- --- --- \n");
			printf("%d |",i+1);
			for(j=0; j<3; j++)
				printf(" %c |",G[i][j]==1 ? 'O' : G[i][j]==0? ' ': 'X');
			printf("\n   --- --- --- \n");
		}

		if(turn%2==0)
		{
			vld_inp = 0;
			while(!vld_inp)
			{
				scanf("%d%c",&row,&col);
				if(G[row-1][col-65]==0)
				{
					G[row-1][col-65]=1;
					vld_inp = 1;
				}
				else
					printf("Wrong input!\n");
			}
			turn++;
		}

		else
		{
			c = 0;

			for(i=2; i>=0; i--)
				for(j=2; j>=0; j--)
				{
					c *= 3;
					c += G[i][j];
				}

			G[new_f[sel][c]/3][new_f[sel][c]%3]=2;
			turn++;
		}

		system("clear");
		for(i=0; i<3; i++)
		{
			if(!i)
				printf("    A   B   C\n   --- --- --- \n");
			printf("%d |",i+1);
			for(j=0; j<3; j++)
				printf(" %c |",G[i][j]==1 ? 'O' : G[i][j]==0? ' ': 'X');
			printf("\n   --- --- --- \n");
		}

		if(outcome()!=0)
			break;
	}


	return 0;
}
