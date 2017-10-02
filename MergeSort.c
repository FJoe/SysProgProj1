#include <stdio.h>
#include <stdlib.h>
#include "Sorter.h"

/*
	Currently can only sort integers
*/

void merge(DataRow ** array, int left, int mid, int right)
{
	char dataType = array[0]->dataType;
	int tempLeftArraySize = mid - left + 1;
	int tempRightArraySize = right - mid;

	//create temporary arrays, since we do not know how big these arrays will be, put them into heap to avoid stackoverflow
	DataRow ** tempLeftArray = (DataRow **)malloc(tempLeftArraySize * sizeof(DataRow));
	DataRow ** tempRightArray = (DataRow **)malloc(tempRightArraySize * sizeof(DataRow));

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
	

	//i is index of  leftArray, j is index of rightArray, k is index of original array
	i = 0;
	j = 0;
	int k = left;

	if(dataType == 'n'){
		//comparison, compares left array with right array and the smaller value is put into original array
		while(i < tempLeftArraySize && j < tempRightArraySize)
		{
			if(tempLeftArray[i]->dataCompare->numData <= tempRightArray[j]->dataCompare->numData)
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

void mergeSort(DataRow ** array, int left, int right)
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
	DataRow** list = (DataRow**) malloc(sizeof(DataRow*) * 2);

	char * s = (char *) malloc(3 * sizeof(char));
	s[0] = 'h';
	s[1] = 'e';
	s[2] = '\0';
	
	DataRow* dataRow1 = (DataRow*) malloc(sizeof(DataRow));
	dataRow1->dataType = 'n';
	dataRow1->data = s;
	
	DataCompare * dataRow1Compare = (DataCompare *) malloc(sizeof(DataCompare));
	dataRow1Compare -> numData = 5;

	dataRow1 -> dataCompare = dataRow1Compare;

	list[0] = dataRow1;

	
	////////

	char * s1 = (char *) malloc(3 * sizeof(char));
	s[0] = 't';
	s[1] = 'i';
	s[2] = '\0';
	
	DataRow* dataRow2 = (DataRow*) malloc(sizeof(DataRow));
	dataRow2->dataType = 'n';
	dataRow2->data = s1;
	
	DataCompare * dataRow2Compare = (DataCompare *) malloc(sizeof(DataCompare));
	dataRow2Compare -> numData = 4;

	dataRow2 -> dataCompare = dataRow2Compare;

	list[1] = dataRow2;

	printf("list %s\n", list[0]->data);
	
	int arraySize = 2;
	
	
	//mergeSort(list, 0, (arraySize-1));
	
	int i;

	for(i = 0; i < arraySize; i++)
	{
		printf("Data Compare:%f ", list[i]->dataCompare->numData); 
		printf("Data: %s \n", list[i]->data);
	}
	
	
	printf("\n");

	

	free(s);
	free(s1);
	free(list);
	free(dataRow1);
	free(dataRow2);
	free(dataRow1Compare);
	free(dataRow2Compare);
	

	return 0;
}

