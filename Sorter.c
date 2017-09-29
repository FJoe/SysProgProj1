#include "Sorter.h"

/**
void printRow(DataRow row)
{
	prin
}
**/

int main(int argc, char* argv[])
{
	//Check if valid input
	if(argc < 2){
		printf("ERROR: no arguments\n");
		return -1;
	}
	if(strcmp(argv[1], "-c") != 0){
		printf("ERROR: not sorting by columns\n");
		return -1;
	}
	if(argc < 3){
		printf("ERROR: column to sort by not given\n");
		return -1;
	}

	//Create copy of column heading to print
	char row1[1024];
	char header[1024]; 
	scanf("%1024[^\n]", row1);
	strcpy(header, row1);

	//If column to search for is found, get column number
	char* colToSort = argv[2];
	int colNumToSort = 0;
	const char delim[2] = ", ";
	char* curHead = strtok(row1, delim);

	while( curHead != NULL && strcmp(colToSort, curHead) != 0){
		curHead = strtok(NULL, delim);
		colNumToSort++;
	}
	if(curHead == NULL){
		printf("ERROR: column to sort not found");
		return -1;
	}

	//Print column headers to output file
	printf("%s\n", header);

	
	return 0;
}
