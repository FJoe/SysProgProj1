#include <stdio.h>
#include <stdlib.h>
#include "Sorter.h"

/*
	Currently can only sort integers
*/

void merge(int * array, int left, int mid, int right)
{
	int tempLeftArraySize = mid - left + 1;
	int tempRightArraySize = right - mid;

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
		tempRightArray[j] = array[mid + j + 1];
	}
	

	//i is index of leftArray, j is index of rightArray, k is index of original array
	i = 0;
	j = 0;
	int k = left;

    //comparison, compares left array with right array and the smaller value is put into original array
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
	
	//copy remaining elements in left array back into the original array
	for(i; i < tempLeftArraySize; i++, k++){
	    array[k] = tempLeftArray[i];
	}

    //copy remaining elements in right array back into the original array
    for(j; j < tempRightArraySize; j++, k++){
	    array[k] = tempRightArray[j];
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
	else{
	    return;
	}
}
 


int main(int argc, char* argv[]){
	//test

	int array[] = {2, 1, 6, 4, 5, 3, 5, 7, 11, 2};
	int arraySize = sizeof(array)/sizeof(int);

	mergeSort(array, 0, (arraySize - 1));
	
	int i;

	for(i = 0; i < arraySize; i++)
	{
		printf("%d ", array[i]); 
	}

	printf("\n");

	return 0;
}

