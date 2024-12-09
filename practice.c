#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char **argv)
{
	char file_line[50];
	FILE *input = fopen("C:/Users/Daniel/Projects/C C++/pace.txt", "r");
	fgets(file_line, 100, input);
	
	printf("%s\n", file_line);
	
	return 0;
}