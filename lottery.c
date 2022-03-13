#include <stdio.h>
#include <stdlib.h>


int* appearances(int **matrixNumbers, int rows){							//returns an array[50] with the number of appearances for each number 1-49, f(n)
	int i, j;
	int *appears = calloc(49, sizeof(int));
	for(i = 0; i < rows; i++){
		for(j = 0; j < 7; j++){
			appears[matrixNumbers[i][j] - 1]++;
		}
	}
	for(i = 0; i < 49; i++)
	return appears;
}

int* bestNumbers(int *matrix, int numbers){									//gets a 1D array representing numbers 1-49 and returns an array with the best numbers numbers 1-49
	int *best = malloc(numbers * sizeof(int));
	int max = -10000;
	int index, i, j;
	for(i = 0; i < numbers; i++){
		for(j = 0; j < 49; j++){
			if(matrix[j] > max){
				max = matrix[j];
				index = j;
			}
		}
		best[i] = index + 1;
		matrix[index] = -10000;
		max = -10000;
	}
	return best;
}

double* bestNumbersDouble(double *matrix, int numbers){						//same us bestNumbers but for double matrix
	double *best = malloc(numbers * sizeof(double));
	double max = -10000;
	int index, i, j;
	for(i = 0; i < numbers; i++){
		for(j = 0; j < 49; j++){
			if(matrix[j] > max){
				max = matrix[j];
				index = j;
			}
		}
		best[i] = index + 1;
		matrix[index] = -10000;
		max = -10000;
	}
	return best;
}

int* lastUsed(int **matrixNumbers, int rows){								//returns an array[50] with the line each number appeared last time on matrixNumbers, d(n)
	int i, j;
	int *last = malloc(49 * sizeof(int));
	for(i = 0; i < 49; i++)													//we assume each numbers has d(n) = K aka rows
		last[i] = rows;
	for(i = rows - 1; i > -1; i--){
		for(j = 6; j > -1; j--){
			last[matrixNumbers[i][j] - 1] = i;
		}
	}
	return last;
}

void metricZero(int **matrixNumbers, int numbers, int rows){				//printng array with mostOften appeared numbers "f(n)"
	int *mostOften;
	int i;
	mostOften = bestNumbers(appearances(matrixNumbers, rows), numbers);
	for(i = 0; i < numbers; i++)
		printf("%d ", mostOften[i]);
	printf("\n");
}

void metricOne(int **matrixNumbers, int numbers, int rows){					//printing array with most not seen in last rows numbers "d(n)"
	int *last;
	int i;
	last = bestNumbers(lastUsed(matrixNumbers, rows), numbers);
	for(i = 0; i < numbers; i++)
		printf("%d ", last[i]);
	printf("\n");
}

void metricTwo(int **matrixNumbers, int numbers, int rows){					//printing array with best f(n) + d(n) numbers
	int *lastPlusOften = malloc(50 * sizeof(int));
	int *last = lastUsed(matrixNumbers, rows);
	int *appears = appearances(matrixNumbers, rows);
	int i;
	for(i = 0; i < 50; i++)
		lastPlusOften[i] = appears[i] + last[i];
	lastPlusOften = bestNumbers(lastPlusOften, numbers);
	for(i = 0; i < numbers; i++)
		printf("%d ", lastPlusOften[i]);
	printf("\n");
}

void metricThree(int **matrixNumbers, int numbers, int rows){				//printing array with best rd(n) numbers "d(n) - K/f(n)"
	double *related = malloc(50 * sizeof(double));
	int* last = lastUsed(matrixNumbers, rows);
	int* appears = appearances(matrixNumbers, rows);
	int i;
	for(i = 0; i < 50; i++){
		if(appears[i] != 0){
			related[i] = (double) last[i] - (double) rows / appears[i];
		}
		else
			related[i] = 0;
	}
	related = bestNumbersDouble(related, numbers);
	for(i = 0; i < numbers; i++)
		printf("%d ", (int) related[i]);
	printf("\n");
}


int main(int argc, char *argv[]) {
	int numbers, metric;							//inputs of user
	char fileName[100];
	FILE *file;										//pointer for file with numbers
	int i, j, rows;									//counters we use for loops etc
	
	scanf("%d %d", &numbers, &metric);				//getting inputs and checking validity
	scanf("%s", fileName);
	if(numbers < 1 || numbers > 49 || metric < 0 || metric > 3){
		printf("Wrong Input!\n");
		return 1;
	}
	if((file = fopen(fileName, "r")) == NULL){
		printf("File Error!\n");
		return 1;
	}
	
	rows = 1;
	while(!feof(file)){								//getting how many rows we have
		if(fgetc(file) == '\n')
			rows++;
	}
	rewind(file);
	int **matrixNumbers = malloc(rows * sizeof(int *));			//making rows * 7 matrix with the lottery numbers
	for(i = 0; i < rows; i++){
		matrixNumbers[i] = malloc(7 * sizeof(int));
	}
	for(i = 0; i < rows; i++){
		for(j = 0; j < 7; j++){
			fscanf(file, "%d", &matrixNumbers[i][j]);
		}
	}
	switch(metric){
		case 0:
			metricZero(matrixNumbers, numbers, rows);
			break;
		case 1:
			metricOne(matrixNumbers, numbers, rows);
			break;
		case 2:
			metricTwo(matrixNumbers, numbers, rows);
			break;
		case 3:
			metricThree(matrixNumbers, numbers, rows);
			break;
	}
	fclose(file);
	return 0;
}
