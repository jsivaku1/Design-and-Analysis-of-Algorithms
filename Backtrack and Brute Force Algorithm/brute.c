#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

struct knapSol
{
	int TotalWeight, TotalProfit, Deleted;
	int profitMatrix[8];
	int weightMatrix[8];
};



void rev(int *itemArr, int curr, int prev)
{
	int tmp;
	while(curr<prev)
	{
		tmp = itemArr[curr];
		itemArr[curr] = itemArr[prev];
		itemArr[prev] = tmp;
		curr++;
		prev--;
	}
}

void incre(int *combine)
{
	int i, remain = 0;
	i=7;
	while(i >= 0)
	{
		if(remain == 0)
		{
			if( combine[i] == 0)
			{
				combine[i]=1;
				break;
			}
			else if( combine[i] == 1)
			{
				combine[i] = 0;
				remain = 1;
			}
		}
		else if( remain == 1)
		{
			if(combine[i] == 0)
			{
				combine[i] = 1;
				remain =0;
				break;
			}
			else if( combine[i] == 1)
			{
				combine[i] = 0;
			}
		}
		i--;
	}
}


int powFn(int base,int expo)
{
	int ans = 1;
	int i;
	i=1;
	while(i<=expo)
	{
		ans = ans * base;
	i++;
	}
	return ans;
}


void ksBruteForce(int *profitMatrix, int *weightMatrix, int *knapsack, int capacity, int n)
{
	int itemArr[n];
	int combine[8];
	int maximum,  optiIndex,tmp=0, curr=0, count = 0;
	int i, j;
	FILE *fp;
	
	maximum = powFn(2, n);
	struct knapSol optiSoln[maximum];
	
	fp= fopen("brute_output.txt", "w");
	combine[0] = 0;
	combine[1] = 0;
	combine[2] = 0;
	combine[3] = 0;
	combine[4] = 0;
	combine[5] = 0;
	combine[6] = 0;
	combine[7] = 1;
	
	i=0;
	while(i< maximum)
	{
		optiSoln[i].Deleted = 0;
		optiSoln[i].TotalProfit = 0;
		optiSoln[i].TotalWeight = 0;
		j=0;
		while(j<8)
		{
			optiSoln[i].weightMatrix[j] = 0;
			optiSoln[i].profitMatrix[j] = 0;
			j++;
		}
		i++;
	}
	
	
	while(curr < maximum)
	{
		
		rev(combine, 0, 7);
		i=0;
		while(i<n)
		{
			optiSoln[curr].profitMatrix[i] = combine[i] * profitMatrix[i];
			optiSoln[curr].weightMatrix[i] = combine[i] * weightMatrix[i];
		i++;
		}
		rev( combine, 0,7);
		
		i=0;
		while(i<8)
		{
			optiSoln[curr].TotalWeight = optiSoln[curr].TotalWeight + optiSoln[curr].weightMatrix[i];
			optiSoln[curr].TotalProfit = optiSoln[curr].TotalProfit + optiSoln[curr].profitMatrix[i];
		i++;
		}
		
		incre(combine);
		curr++;
	}

	i=0;
	while(i < maximum)
	{
		if(optiSoln[i].TotalWeight > capacity)
		{
			optiSoln[i].Deleted = 1;
		}
		i++;
	}
	

	
	i=0;
	while(i<maximum)
	{
		if((optiSoln[i].TotalProfit > tmp) && (optiSoln[i].Deleted != 1))
		{	
			tmp = optiSoln[i].TotalProfit;
			optiIndex = i;
		}
		i++;
	}
	
	fprintf(fp, "%d\n", optiSoln[optiIndex].TotalWeight);
	fprintf(fp, "%d\n", optiSoln[optiIndex].TotalProfit);
	
	j=1;
	i=0;
	while(i < n)
	{
		if(optiSoln[optiIndex].profitMatrix[i] != 0)
		{
			itemArr[j] = i;
			count = count+1;
			
			j++;
		}
		i++;
	}
	
	j=1;
	while(j<=count)
	{
	fprintf(fp, "%d", itemArr[j]);
	if(j<count)
			fprintf(fp, ", "); 
	j++;
	}
	fclose(fp);
	
}

int main(int argc, char **argv)
{  
if(argc != 2)                                                       
            {
                printf("ERROR:\nUSAGE: filename [INPUT_FILENAME]\n");
                return 0;
            }
	int *weightMatrix, *profitMatrix,  *ksMatrix; 
	int capacity=0, rows=0;
	int i, n;

	    
        FILE *fp;

 fp=fopen(argv[1],"r");
   
      fscanf(fp, "%d", &rows);
    
    fclose(fp);
        n=rows;

	weightMatrix = malloc(n * sizeof(int));
	profitMatrix = malloc(n * sizeof(int));
	ksMatrix = malloc(n * sizeof(int));
	
	i=0;
	while(i<n)
	{
		weightMatrix[i] = 0;
		profitMatrix[i] = 0;
		ksMatrix[i] = 999;
		i++;
	}

	fp=fopen(argv[1],"r");
    rows = fgetc(fp);
	
	i=0;
    while(i<n)
                {
                        
                        fscanf(fp,"%d%*[,]",&weightMatrix[i]);
                                             
                i++;
                }
	
	i=0;
    while(i<n)
                {
                        
                        fscanf(fp,"%d%*[,]",&profitMatrix[i]);
                                            
                i++;
                }
	
	fscanf(fp, "%d", &capacity);
	
/*	printf("\nCapacity is %d", capacity);
	printf("\nweight: ");
	i=0;
    while(i<n)
                
                {       
                                        printf("\t%d\t",weightMatrix[i]);
                                i++;
                                }
                printf("\n");
	printf("\nprofit: ");
	
	i=0;
    while(i<n)
                
                {       
                                        printf("\t%d\t",profitMatrix[i]);
                                     i++;
                                }
                printf("\n");   
*/
	ksBruteForce(profitMatrix, weightMatrix, ksMatrix, capacity, n);
	free(weightMatrix);
	free(profitMatrix);
	free(ksMatrix);	
	return 0; 
}
