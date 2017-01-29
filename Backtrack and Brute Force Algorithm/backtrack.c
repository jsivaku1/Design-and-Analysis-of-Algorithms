#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int number=0;
int MaximumProfit=0;

void sortFn(int *weightMatrix, int *profitMatrix, int n)
{
float item[n];
float tmp2;
int i,j;
int tmp,tmp1;
i=1;
while(i<=n)
{
item[i] = (float) profitMatrix[i+1] / (float) weightMatrix[i+1];
i++;
}

i=1;
while(i<n)
   {
	   j=i+1;
   while(j<=n)
      {
      if(item[i] <= item[j])
         {
         tmp2 = item[i];
         item[i] = item[j];
         item[j] = tmp2;
         tmp = profitMatrix[i];
         profitMatrix[i] = profitMatrix[j];
         profitMatrix[j] = tmp;
         tmp1 = weightMatrix[i];
         weightMatrix[i] = weightMatrix[j];
         weightMatrix[j] =tmp1;
         }
      j++;
	  }
    i++;
	}
}


float limit(int i, int w, int p, int *weightMatrix, int *profitMatrix, int capacity, int n)
{
	int benefit[n];
	float limit;
	int j = 0;
	int temp;
	limit = p;
	j=i;
	while(j<=n)
	{
		benefit[j] = 0;
		j++;
	}
	while((w < capacity) && (i<=n))
	{
		temp = w + weightMatrix[i];
		if( temp <= capacity)
		{
			benefit[i]=1;
			w +=  weightMatrix[i];
			limit += profitMatrix[i];
		}
		else
		{
			benefit[i] = (capacity - w)/weightMatrix[i];
			w = capacity;
			limit += profitMatrix[i]*benefit[i];
		}	
		i += 1;
	}
	return limit;
}	

int optimal(int i, int w, int p, int *weightMatrix, int *profitMatrix, int capacity, int n)
{
	float lim;
	if( w >= capacity)
		return 0;
	lim = limit(i+1, w, p, weightMatrix, profitMatrix, capacity, n);
	return (lim > MaximumProfit);
}

void Backtrack(int i, int w, int p, int *weightMatrix, int *profitMatrix, int capacity, int n, int *incMatrix, int *bestMatrix)
{
	int j;
	if(w <= capacity && p > MaximumProfit)
	{
		MaximumProfit = p;
		number = i;
		j=1;
		while(j<=number){
			bestMatrix[j] = incMatrix[j];
		j++;
	}
	}
	
	if(optimal(i, w, p, weightMatrix, profitMatrix, capacity, n))
	{
		incMatrix[i+1] = 1;
		Backtrack(i+1, w + weightMatrix[i+1], p + profitMatrix[i+1], weightMatrix, profitMatrix, capacity, n, incMatrix, bestMatrix);
		incMatrix[i+1] = 0;
		Backtrack(i+1, w, p, weightMatrix, profitMatrix, capacity, n, incMatrix, bestMatrix);
	}
} 

void ksBacktrack(int i, int p, int w, int *weightMatrix, int *profitMatrix, int capacity, int n)
{
	int itemArr[n];
	int *incMatrix, *bestMatrix;
	int j; 
	int totalWeight = 0, count=0;
	FILE *fp;
	incMatrix = malloc((n+1) * sizeof(int));
	bestMatrix = malloc((n+1) * sizeof(int));
	MaximumProfit = 0;
	number = 0;
	fp = fopen("backtrack_output.txt", "w");
	i=1;
	while(i<=n)
	{
		incMatrix[i] = -1;
		bestMatrix[i] = -1;
		i++;
	}
	Backtrack(0, 0, 0, weightMatrix, profitMatrix, capacity, n, incMatrix, bestMatrix);
	i=1;
	while(i<=n)
	{
		if(bestMatrix[i] == 1)
		{
			totalWeight += weightMatrix[i];
		}
		i++;
	}
	fprintf(fp, "%d\n", totalWeight);
	fprintf(fp, "%d\n", MaximumProfit);
	j=1;
	i=1;
	while(i <= n)
	{
		if(bestMatrix[i] == 1)
		{
			itemArr[j] = i-1;
			count += 1;
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
	free(bestMatrix);
	free(incMatrix);	
}	

int main(int argc, char **argv)
{  
	if(argc != 2)                                                       
            {
                printf("ERROR:\nUSAGE: filename [INPUT_FILENAME]\n");
                return 0;
            }
	int	*weightMatrix,*profitMatrix, *ksMatrix; 
	int capacity=0, rows=0;
	int i, n;
    FILE *fp;
	fp=fopen(argv[1],"r");
    fscanf(fp, "%d", &rows);
    fclose(fp);
    n=rows;
	profitMatrix = malloc(n * sizeof(int));
	weightMatrix = malloc(n * sizeof(int));
	ksMatrix = malloc(n * sizeof(int));
	i=1;
	while(i<=n)
	{
		ksMatrix[i] = 999;
		weightMatrix[i] = 0;
		profitMatrix[i] = 0;
		i++;
	}
	fp=fopen(argv[1],"r");
    rows = fgetc(fp);
	i=1;
    while(i<=n)
                {
                        
                        fscanf(fp,"%d%*[,]",&weightMatrix[i]);                                 
                i++;
                }
	i=1;
    while(i<=n)
                {
                        
                        fscanf(fp,"%d%*[,]",&profitMatrix[i]);                    
                i++;
                }
	fscanf(fp, "%d", &capacity);
/*	printf("\nweight: ");
	 i=1;
    while(i<=n)
                
                {       
                                        printf("\t%d\t",weightMatrix[i]);
                                i++;
                                }
                printf("\n");
       
     

	
	printf("\nprofit: ");
	 i=1;
    while(i<=n)
                
                {       
                                        printf("\t%d\t",profitMatrix[i]);
                                     i++;
                                }
                printf("\n"); */
	sortFn(weightMatrix, profitMatrix, n);
	ksBacktrack(0, 0, 0, weightMatrix, profitMatrix, capacity, n);
	free(weightMatrix);
	free(profitMatrix);
	free(ksMatrix);
	return 0; 
}

