//Daniel van Dijke
//Pacecalc function for miles

#include <stdio.h>
#include <string.h>

void miles(char, float, float){
	
	
	float *mmin;
	float *msecs;
	
	printf("How many minutes? \n");
	fgets(mmin, 20, stdin);
	
	int mminlen = strlen(mmin);
	if (mminlen > 0 && mmin[mminlen - 1] == '\n')
		mmin[mminlen - 1] = '\0';
	
	printf("How many seconds? \n");
	fgets(msecs, 20, stdin);
	
	int msecslen = strlen(msecs);
	if (msecslen > 0 && msecs[msecslen - 1] == '\n')
		msecs[msecslen - 1] = '\0';
	
	
	
	
}