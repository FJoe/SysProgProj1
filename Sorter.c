#include "Sorter.h"

char* trimSpace(char* str){
	int end = strlen(str) - 1;
	while(str[end] == ' ' || str[end] == '\n')
	{
		str[end] = '\0';
		end--;
	}
	

	while(*str == ' ')
	{
		str++;
	}

	return str;
}

char getDataType(char* data){
	if(strcmp(data, "color") == 0)
		return 's';
 	else if(strcmp(data, "director_name") == 0)
		return 's'; 
	else if(strcmp(data, "actor_2_name") == 0)
		return 's';
	else if(strcmp(data, "genres") == 0)
		return 's';
	else if(strcmp(data, "actor_1_name") == 0)
		return 's';
	else if(strcmp(data, "movie_title") == 0)
		return 's';
	else if(strcmp(data, "actor_3_name") == 0)
		return 's';
	else if(strcmp(data, "plot_keywords") == 0)
		return 's';
	else if(strcmp(data, "movie_imdb_link") == 0)
		return 's';
	else if(strcmp(data, "language") == 0)
		return 's';
	else if(strcmp(data, "country") == 0)
		return 's';
	else if(strcmp(data, "content_rating") == 0)
		return 's';

	if(strcmp(data, "num_critic_for_reviews") == 0)
		return 'n';
	else if(strcmp(data, "duration") == 0)
		return 'n'; 
	else if(strcmp(data, "director_facebook_likes") == 0)
		return 'n'; 
	else if(strcmp(data, "actor_3_facebook_likes") == 0)
		return 'n';
	else if(strcmp(data, "actor_1_facebook_likes") == 0)
		return 'n';
	else if(strcmp(data, "gross") == 0)
		return 'n';
	else if(strcmp(data, "num_voted_users") == 0)
		return 'n';
	else if(strcmp(data, "cast_total_facebook_likes") == 0)
		return 'n';
	else if(strcmp(data, "facenumber_in_poster") == 0)
		return 'n';
	else if(strcmp(data, "num_user_for_reviews") == 0)
		return 'n';
	else if(strcmp(data, "budget") == 0)
		return 'n';
	else if(strcmp(data, "title_year") == 0)
		return 'n';
	else if(strcmp(data, "actor_2_facebook_likes") == 0)
		return 'n';
	else if(strcmp(data, "imdb_score") == 0)
		return 'n';
	else if(strcmp(data, "aspect_ratio") == 0)
		return 'n';
	else if(strcmp(data, "movie_facebook_likes") == 0)
		return 'n';


	return 'e';
		
}

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
	char* row1 = (char*) calloc(1024, sizeof(char));
	if(fgets(row1, sizeof(char) * 1024, stdin) == NULL){
		printf("ERROR: file empty");
		return -1;
	}

	//Print column headers to output file
	printf("%s", row1);

	//If column to search for is found, get column number
	char* colToSort = argv[2];
	int colNumToSort = 0;
	const char delim[2] = ",";
	char* curHead = strtok(row1, delim);

	while( curHead != NULL && strcmp(colToSort, curHead) != 0){
		curHead = strtok(NULL, delim);
		colNumToSort++;
	}
	if(curHead == NULL){
		printf("ERROR: column to sort not found");
		return -1;
	}

	//Creating list of DataRow
	DataRow** list = (DataRow**) malloc(sizeof(DataRow*) * 10000);
	char dataType = getDataType(colToSort);
	int curRowNum = 0;
	
	char* origRow = (char*) calloc(1024, sizeof(char));

	
	//Goes through each row in csv file
	while(fgets(origRow, sizeof(char) * 1024, stdin) != NULL){
		//New dataRow for array
		DataRow* newDataRow = (DataRow*) malloc(sizeof(DataRow));
		newDataRow->dataType = dataType;

		//newRow is data for new row with trimmed spaces
		char* newRow = (char*) calloc(1024, sizeof(char));

		//Goes through each word, trimming spaces and finding data to sort by
		char* curWord = strtok(origRow, delim);
		int firstWord = 1;
		int i = 0;
		while(curWord != NULL){
			if(firstWord)
				firstWord = 0;
			else
				strcat(newRow, ",");

			char* trimWord = trimSpace(curWord);

			if(i == colNumToSort){
				DataCompare* newDataCompare = (DataCompare*) malloc(sizeof(DataCompare));
				if(dataType == 'n'){
					newDataCompare->numData = atof(trimWord);
				}
				else if(dataType == 's'){
					newDataCompare->stringData = trimWord;
				}

				newDataRow->dataCompare = newDataCompare;
			}
			

			strcat(newRow, trimWord);
			curWord = strtok(NULL, delim);

			i++;
		}
		newDataRow->data = newRow;
		list[curRowNum] = newDataRow;
		if(curRowNum > 0)	
			printf("%s\n", list[curRowNum-1]->dataCompare->stringData);
		curRowNum++;
	}

	//Sort list
	int j;	
	for(j = 0; j < curRowNum; j++)
	{
		//printf("%s\n", list[j]->dataCompare->stringData);
		if(dataType == 'n')
			;//printf("%f\n", list[j]->dataCompare->numData);
		else if(dataType == 's')
			printf("%s\n", list[j]->dataCompare->stringData);

		free(list[j]->dataCompare);
		free(list[j]->data);
		free(list[j]);
	}
	free(row1);
	free(origRow);
	free(list);
	return 0;
}

















