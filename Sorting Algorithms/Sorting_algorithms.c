#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Function to generate a star visualization when n <= 20
void visualize(int *number,int n)
	{
		int i,j;
		printf("\nVISUALIZATION OF THE SORT\n");
		for(i=0;i<n;i++){
			for(j=1;j<=number[i];j++) 
				printf("*");	
		printf("\n");
		}	
		for (j = 0 ; j <n ; j++) {
			printf("%d\t", number[j]); 
		}
		printf("\n\n");
	}

//Function to generate random number using rand() from 1 to 1000 when n>20
int* generate_array(int n)
	{
		int temp;
		int i;
		long int number[1500];
		for(i=0;i<n;i++){
			number[i]=0;
		}
		srand(time(NULL));
		for(i=0;i<n;i++){
			int r = rand();
			number[i]=r;
		}
		printf("\nNumbers Generated by random function are: \n");
		for(i=0;i<n;i++){
			printf("%ld\t", number[i]);
		}
		printf("\n\n");
		return number;
	}

//Function to generate random number using rand() from 0 to 99 when n>20 only for counting_sort function 
int* generate_array_countingsort(int n)
	{
		int i;
		long int number[1500];
		for(i=0;i<n;i++){
			number[i]=0;
		}
		srand(time(NULL));
		for(i=0;i<n;i++){
			int r = rand() % 100;
			number[i]=r;
		}
		printf("\nNumbers Generated by random function are: \n");
		for(i=0;i<n;i++){
			printf("%ld\t", number[i]);
		}
		printf("\n\n");
		return number;
	}

//Function to generate random number using rand() from 0 to 15 when n <= 20
int* generate_array_15(int n)
	{
		int i;
		long int number[1500];
		for(i=0;i<n;i++){
			number[i]=0;
		}
		srand(time(NULL));
		for(i=0;i<n;i++){
			int r = rand() % 15;
			number[i]=r;
		}
		printf("\nNumbers Generated by random function are: \n");
		for(i=0;i<n;i++){
			printf("%ld\t" ,number[i]);
		}
		printf("\n\n");
		return number;
	}

//Insertion sort algorithm for sorting the randomly generated numbers
void insertion_sort(int n)
	{
		int i,j, temp;
		long int *number;
		if(n<=20){
			number = generate_array_15(n);
		}
		else
			number = generate_array(n);
		if(n<=20){
			visualize(number, n);
		}
		for (i = 0 ; i <n ; i++) {
			while ( i > 0 && number[i] < number[i-1]) {
				temp          = number[i];
				number[i]   = number[i-1];
				number[i-1] = temp;
				i--;
			}
			if(n<=20){
				visualize(number, n);
			}
		}
		printf("\nThe Sorted Array is:  \n");
		for (i = 0; i <n; i++) {
			printf("%ld\t", number[i]); 
		}
		printf("\n\n");
	}

//Finding the maximum of two numbers which is used in counting sort algorithm
int maximum(int *array, int size)
	{
		int curr = 0;
		int max = 0;
		for(curr = 0; curr < size; curr++){
			if(array[curr] > max){ max = array[curr]; }
		}
		return max;
	}

//Counting sort algorithm for randomly generated numbers between 0 to 99 
void counting_sort(int n)
	{
		int i, j, curr = 0;
		long int *number;
		if(n<=20){
			number = generate_array_15(n);
		}
		else
			number = generate_array_countingsort(n);
		if(n<=20){
				visualize(number, n);
			}
		int max = maximum(number, n);
		int  *counting_array = calloc(max, sizeof(int));
		for(curr= 0;curr < n; curr++){
			counting_array[number[curr]]++;
		}
		int num = 0;
		curr = 0;
		while(curr <= n){ 
			while(counting_array[num] > 0){
				number[curr] = num;
				counting_array[num]--;
				curr++;
				if(curr > n){ break; }
			}
			if(n<=20){
				visualize(number, n);
			}
			num++;
		}
		printf("\nThe Sorted array is: \n");
		for(curr = 0; curr < n; curr++){
			printf("%ld\t ", number[curr]);
		}
		printf("\n\n");
	}

//Merging two split arrays after sorting them in Merge sort algorithm
void Merge(long int *number,long int *L,int leftCount,long int *R,int rightCount) 
	{
		int i,j,k;
		i = 0; j = 0; k =0;
		while(i<leftCount && j< rightCount) {
			if(L[i]  < R[j]) number[k++] = L[i++];
			else number[k++] = R[j++];
		}
		while(i < leftCount) number[k++] = L[i++];
		while(j < rightCount) number[k++] = R[j++];
	}

//Merge sort algorithm for randomly generated numbers between 1 to 1000
void merge_sort(long int *number, int n, int inputdata)
	{
		long int mid;
		int i,j;
		long int *L, *R;
		if(n<2) return;
		mid = n/2;
		L=(long int*)malloc(mid*sizeof(long int));
		R=(long int*)malloc((n-mid)*sizeof(long int));
		for(i = 0;i<mid;i++) L[i] = number[i]; // creating left subarray
		for(i = mid;i<n;i++) R[i-mid] = number[i]; // creating right subarray
		merge_sort(L,mid, inputdata);  // sorting the left subarray
		merge_sort(R,n-mid, inputdata);  // sorting the right subarray
		Merge(number,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
		if(inputdata<=20){
			visualize(number, inputdata);
		} 
		free(L);
		free(R);
	} 
//Merging two split arrays after sorting them in Merge sort algorithm
void Merge_20(int *number,int *L,int leftCount,int *R,int rightCount) 
	{
		int i,j,k;
		i = 0; j = 0; k =0;
		while(i<leftCount && j< rightCount) {
			if(L[i]  < R[j]) number[k++] = L[i++];
			else number[k++] = R[j++];
		}
		while(i < leftCount) number[k++] = L[i++];
		while(j < rightCount) number[k++] = R[j++];
	}

//Merge sort algorithm for randomly generated numbers between 1 to 1000
void merge_sort_20(int *number, int n, int inputdata)
	{
		int mid;
		int i,j;
		int *L, *R;
		if(n<2) return;
		mid = n/2;
		L=(int*)malloc(mid*sizeof(int));
		R=(int*)malloc((n-mid)*sizeof(int));
		for(i = 0;i<mid;i++) L[i] = number[i]; // creating left subarray
		for(i = mid;i<n;i++) R[i-mid] = number[i]; // creating right subarray
		merge_sort_20(L,mid, inputdata);  // sorting the left subarray
		merge_sort_20(R,n-mid, inputdata);  // sorting the right subarray
		Merge_20(number,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
		if(inputdata<=20){
			visualize(number, inputdata);
		} 
		free(L);
		free(R);
	} 

//Swapping two numbers based on sorting comparisons
void swap(int *lhs, int *rhs)
	{
		if (lhs == rhs)
			return;

		int tmp = *lhs;
		*lhs = *rhs;
		*rhs = tmp;
	}

//Partitioning the array based on the pivot element selected randomly.	
int partition(long int number[], int len)
	{
		int i, pvt=0;
		swap(number + (rand() % len), number+(len-1));
		for (i=0; i<len; ++i){
			if (number[i] < number[len-1])
				swap(number + i, number + pvt++);
		}

		// swap the pivot value into position
		swap(number+pvt, number+(len-1));
		return pvt;
	}

//Randomized quick sort algorithm to generate a pivot randomly in each set and sorting using partition. 
void randomized_quick_sort(long int  number[], int n, int inputdata)
	{
		int j;
		if (n < 2)
			return;
		if(inputdata<=20){
			visualize(number, inputdata);
		}
		int pvt = partition(number, n);
		randomized_quick_sort(number,pvt++,inputdata);
		randomized_quick_sort(number+pvt, n-pvt, inputdata);
	}

//Main function with Sorting technique options which will call all the above sorting algorithms. 
int main()
	{
		int choice=0, n=0;
		int i;
		long int *number;
		int	j, inputdata=0;
		printf("\nEnter number of input data between 1 and 1000:\t");
		scanf("%d", &n);
		printf("\n1. Insertion Sort\n2. Counting Sort\n3. Merge Sort\n4. Randomized Quick Sort");
		printf("\nEnter the sorting algorithm to use:\t"); 
		scanf("%d", &choice);
		if((n<1) && (n >1000)){
			printf("\nError: Enter the number between 1 and 1000");
		}
		else{
			switch(choice)
				{
					case 1:
						printf("\nInsertion Sort Algorithm\n");
						insertion_sort(n);
						break;
					case 2:
						printf("\nCounting Sort Algorithm\n");
						counting_sort(n);
						break;
					case 3:
						printf("\nMerge Sorting Algorithm\n");
						if(n<=20){
							number = generate_array_15(n);
						}
						else{
							number = generate_array(n);
						} 
						inputdata = n;
						if(n<=20) { merge_sort_20(number, n, inputdata); }
						else {	merge_sort(number, n, inputdata); }
						printf("Sorted list in ascending order:\n");
						for (i = 0; i <n; i++) {
							printf("%d\t", number[i]);
						}
						printf("\n\n");
						break;
					case 4:
						printf("\nRandomized Quick Sort Algorithm\n");
						if(n<=20){
							number = generate_array_15(n);
						}
						else
							number = generate_array(n);
						inputdata = n;
						randomized_quick_sort(number, n, inputdata);
						if(n<=20){
							visualize(number, n);
						}
						printf("\nThe sorted array is:  \n");
						for(i = 0;i<n;i++){
							printf("%d\t", number[i]);
						}
						printf("\n\n");
						break;
					default:
						printf("\nError: Enter only the number given for the above sorting algorithm\n");
						break;	
				}
		}
		return 0;
	}
	
