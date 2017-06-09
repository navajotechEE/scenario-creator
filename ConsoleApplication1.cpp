// ConsoleApplication1.cpp
// This program opens two files. It uses  
// fclose to close the first file and  
// _fcloseall to close all remaining files.  
#include "stdafx.h"
#include <stdio.h> 
#include <iostream>

FILE *stream, *stream2;
char aline[200];
char *missionFile="mission.biedi";
int i;
int j;
char position[100] = "                POSITION=\"[";
char buffer[200];

using namespace std;
int main(int argc, char *argv[], char *envp[])
{
	int err;

	int iNumberLines = 0;    // Default is no line numbers.  

							 // If /n is passed to the .exe, display numbered listing  
							 // of environment variables.  
	printf("argc = %d\n", argc);
	for (i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i,argv[i]);

	if ((argc == 2) && _stricmp(argv[1], "/n") == 0)
		iNumberLines = 1;

	// Walk through list of strings until a NULL is encountered.  
	for (int i = 0; envp[i] != NULL; ++i) {
		if (iNumberLines)
			cout << i << ": " << envp[i] << "\n";
	}

	int inc;

	inc = atoi(argv[1]);
	printf("%d\n", inc);
		getchar();

	// Open for read (will fail if file "mission.biedi" does not exist)  
	stream=fopen(missionFile, "r");
	if (stream)
	{
		printf("The file '%s' was opened\n",missionFile);
	}
	else
	{
		printf("The file '%s' was not opened\n", missionFile);
		//getchar();
	}

	// Open new mission file for write  

	stream2=fopen("data2.biedi", "w+");
	if (stream2)
	{
		printf("The file 'data2.biedi' was opened\n");
	}
	else
	{
		printf("The file 'data2.biedi' was not opened\n");
	}

	j = 1000;
	for (i = 0; i < 2000; i++) {
	fgets(aline, 200, stream);
	if (feof(stream))
		break;
	printf("%s", aline);
	if (strstr(aline, "POSITION")) {
		sprintf(buffer, "%s%d,%d,%d]\";", position,j,1000,0);
		j+=inc;
		printf("%s", buffer);
		fputs(buffer, stream2);
		fputs("\n",stream2);
		//getchar();
	}
	else	
		fputs(aline, stream2);
	}

	//fprintf(stream2, "Hello World\n");


	// Close stream if it is not NULL   
	if (stream)
	{
		err = fclose(stream);
		if (err == 0)
		{
			printf("The file 'mission.biedi' was closed\n");
		}
		else
		{
			printf("The file 'mission.biedi' was not closed\n");
		}
	}

	// All other files are closed:  
	int numclosed = _fcloseall();
	printf("Number of files closed by _fcloseall: %u\n", numclosed);

	getchar();
}