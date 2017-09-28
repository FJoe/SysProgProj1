#include <stdio.h>
#include <stdlib.h>
#include "Sorter.h"

/*
	REQUIRES DEBUGGING
	Currently, the arraylist is not being sorted properly.
	Testcase 1: {2, 1} sorts properly
	Testcase 2: if |Size| > 2, then the program breaks down 
	Could you type in the commands here for gdb? 

	Forgot how to compile the program so we can run it in gdb

*/

void merge(int * array, int left, int mid, int right)
{
	int tempLeftArraySize = mid - left;
	int tempRightArraySize = right - mid + 1;

	//create temporary arrays, since we do not know how big these arrays will be, put them into heap to avoid stackoverflow
	int * tempLeftArray = (int *)malloc(tempLeftArraySize * sizeof(int));
	int * tempRightArray = (int *)malloc(tempRightArraySize * sizeof(int));

	int i, j;
	//copy items into left array
	for(i = 0; i < tempLeftArraySize; i++)
	{	
		//purpose of [left + j] is the mergesort can happen at different part of the original array
		tempLeftArray[i] = array[left + i];
	}
	
	//copy items into right array
	for(j = 0; j < tempRightArraySize; j++)
	{
		tempRightArray[j] = array[mid + 1 + j];
	}

	//i is index of leftArray, j is index of rightArray, k is index of original array
	i = 0;
	j = 0;
	int k = 0;

	while(i < tempLeftArraySize && j < tempRightArraySize)
	{
		if(tempLeftArray[i] <= tempRightArray[j])
		{
			array[k] = tempLeftArray[i];
			i++;
		}
		else
		{
			array[k] = tempRightArray[j];
			j++;
		}

		k++;
	}

	while(i < tempLeftArraySize)
	{
		array[k] = tempLeftArray[i];
		i++;
		k++;
	}

	while(j < tempRightArraySize)
	{
		array[k] = tempRightArray[j];
		j++;
		k++;		
	}

	free(tempLeftArray);
	free(tempRightArray);
}

void mergeSort(int * array, int left, int right)
{
	int mid;

	//if true, there is more than one element in the array
	if(left < right)
	{
		mid = (left + right) / 2;
		mergeSort(array, left, mid);
		mergeSort(array, mid + 1, right);
		merge(array, left, mid, right);
	}
	else 
	{
		return;
	}
}



int main(int argc, char* argv[]){
	//test

	int array[] = {2, 1, 4, 3};

	int arraySize = sizeof(array)/sizeof(int);

	printf("array size: %d \n", arraySize);

	mergeSort(array, 0, arraySize - 1);

	int i;

	for(i = 0; i < arraySize; i++)
	{
		printf("%d ", array[i]); 
	}

	printf("\n");

	return 0;
}


