//Daniel van Dijke
//Program to calculate pace of a run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char buffer[50];
	char unit[50];
	char sing_unit[50];
	char cdist[20];
	char ctime[20];
	char opp_unit[50];
	char sing_opp_unit[50];
	//float miles = 0.621371;
	//float km = 1;
	//float conversion = 0;
	char date[10];
	float opp_pace;
	int opp_pacemins;
	int opp_pacesecs;
	float opp_dist;
	
	int flag = 1;
	while (flag)
	{
	
	printf("Enter date you ran in format 00/00/00\n");
	fgets(date, 10, stdin);
	int dlen = strlen(date);
		if (dlen > 0 && date[dlen - 1] == '\n')
		{
			date[dlen - 1] = '\0';
		}
		
		if (dlen < 9)
		{
			printf("Invalid date format\n");
		}
		else
		{
			flag = 0;
		}
	}
		
	//generate conversion factor
	flag = 1;
	while (flag)
	{
	
		printf("To select unit of distance type either 'm' or 'k': \n");
		fgets(buffer, 50, stdin);
	
		int len = strlen(buffer);
		if(len > 0 && buffer[len - 1] == '\n')
			buffer[len - 1] = '\0';
			
			unit[0] = '\0';
			opp_unit[0] = '\0';
			sing_unit[0] = '\0';
			sing_opp_unit[0] = '\0';
			 

		if (strcmp(buffer, "m") == 0)
		{
			strcat(unit, "miles");
			strcat(opp_unit, "kilometers");
			strcat(sing_unit, "mile");
			strcat(sing_opp_unit, "kilometer");
			flag = 0;
		}
	
		else if (strcmp(buffer, "k") == 0)
		{
			strcat(unit, "kilometers");
			strcat(opp_unit, "miles");
			strcat(sing_unit, "kilometer");
			strcat(sing_opp_unit, "mile");
			flag = 0;
		}
	
		else
		{
			printf("Invalid argument\n");
		}
	}
	
	//Prompt for distance run
	printf("Please enter distance run: \n");
	fgets(cdist, 20, stdin);
	float dist = atof(cdist);
	
	//Prompt for time in form xx:xx
	printf("Enter time ran in form 'xx:xx' ");
		fgets(ctime, 20, stdin);
	
	//convert time in a decimal form in minutes
	char *delimiters = ":.";
	char *token = strtok(ctime, delimiters);
	
	//calculate pace
	float mins = atof(token);
	token = strtok(NULL, delimiters);
	float secs = atof(token);
	
	float time = mins + (secs / 60);
	
	float pace = (time / dist);
	
	//convert pace back to minutes and seconds
	int pacemins = (int)pace;
	float fpacesecs = (pace - pacemins) * 60;
	int pacesecs = (int)fpacesecs;
	
	
	if (strcmp(opp_unit, "miles") == 0)
	{
		opp_dist = 0.621371 * dist;
		opp_pace = 1.60934 * pace;
		opp_pacemins = (int)opp_pace; 
		opp_pacesecs = (opp_pace - opp_pacemins) * 60;
	}
	
	else if (strcmp(opp_unit, "kilometers") == 0)
	{
		opp_dist = 1.60934 * dist;
		opp_pace = 0.621371 * pace;
		opp_pacemins = (int)opp_pace; 
		opp_pacesecs = (opp_pace - opp_pacemins) * 60;
	}
	
	//print result in both km and miles
	printf("\nOn %s, \nyou ran %.2f %s in a time of %.f minutes and %.f seconds at a pace of %d minutes and %d seconds per %s.\n", 
	date, dist, unit, mins, secs, pacemins, pacesecs, sing_unit);
	printf("In %s, that's %.2f %s at a pace of %d minutes and %d seconds per %s.\n",
	opp_unit, opp_dist, opp_unit, opp_pacemins, opp_pacesecs, sing_opp_unit);
	
	return 0;
}

//Should prompt for a distance unit
//If it's in miles it should just be the same except everything is * 1.6
