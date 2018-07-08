#include <stdio.h>
#include <stdlib.h>

/*
Simple code to demonstrate Benford law, from a txt file;
The txt file must be formed only with integers numbers > 0;
by Talyson Rodrigues;
*/

unsigned int getPrimaryDigit(long unsigned int n);
long int getLinesNumber(char *fileName);
long unsigned int * readNumbers(char *fileName);

int main(int argc, char **argv){
	unsigned int digit;
	long int linesNumber = getLinesNumber(argv[1]), i;
	long unsigned int * vet = readNumbers(argv[1]);
	long int vectorBenford[10];
	
	if(!(argc == 2)){
		printf("Usage is %s nameFile\n", argv[0]);
		exit(-1);
	}
	
	for(i = 0; i < 10;i++){
		vectorBenford[i] = 0;
	}
	
	for(i = 0; i < linesNumber;i++){		
		digit = getPrimaryDigit(vet[i]);
		vectorBenford[digit]++;
	}
	printf("Digit\t\tFile\t\tBenford\n");
	printf("1\t\t%2.2lf%%\t\t30.10%%\n", (double) vectorBenford[1] / linesNumber * 100);
	printf("2\t\t%2.2lf%%\t\t17.60%%\n", (double) vectorBenford[2] / linesNumber * 100);
	printf("3\t\t%2.2lf%%\t\t12.50%%\n", (double) vectorBenford[3] / linesNumber * 100);
	printf("4\t\t%2.2lf%%\t\t9.70%%\n", (double) vectorBenford[4] / linesNumber * 100);
	printf("5\t\t%2.2lf%%\t\t7.90%%\n", (double) vectorBenford[5] / linesNumber * 100);
	printf("6\t\t%2.2lf%%\t\t6.70%%\n", (double) vectorBenford[6] / linesNumber * 100);
	printf("7\t\t%2.2lf%%\t\t5.80%%\n", (double) vectorBenford[7] / linesNumber * 100);
	printf("8\t\t%2.2lf%%\t\t5.10%%\n", (double) vectorBenford[8] / linesNumber * 100);
	printf("9\t\t%2.2lf%%\t\t4.60%%\n", (double) vectorBenford[9] / linesNumber * 100);
	printf("\nTotal lines number is %ld\n" ,linesNumber);
	
	free(vet);
	
	return 0;
}

unsigned int getPrimaryDigit(long unsigned int n){
	long unsigned int previous;
	while(n != 0){
		previous = n;
		n = n / 10;
	}
	return previous;
}

long int getLinesNumber(char *fileName){
	char buffer[1024];
	long int count = 0;
	FILE * fp = fopen(fileName, "r");
	if(fp == NULL){
		perror("Error: ");
		exit(-1);
	}
	while(!feof(fp)){
		fgets(buffer, 1024, fp);
		count++;
	}
	pclose(fp);
	return count;
}

long unsigned int * readNumbers(char *fileName){
	long unsigned int linesNumber = getLinesNumber(fileName), count = 0, i;
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL){
		perror("Error: ");
		exit(-1);
	}
	long unsigned int *lines = (long unsigned int *) malloc(linesNumber * sizeof(long unsigned int));
	if(lines == NULL){
		perror("Error: ");
		exit(-1);
	}
	while(!feof(fp)){
		fscanf(fp, "%lu", &lines[count]);
		count++;
	}
	pclose(fp);
	return lines;
}

