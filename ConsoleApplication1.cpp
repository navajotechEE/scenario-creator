// ConsoleApplication1.cpp
// This program opens two files. It uses  
// fclose to close the first file and  
// _fcloseall to close all remaining files.  
//#include "stdafx.h"
#include <stdio.h> 
#include <string.h>
#include <iostream>

FILE *stream, *stream2;
char aline[500];
char missionFile[]="mission.biedi";
int i;
int x,y,z;
char position[500] = "                POSITION=\"[";
char buffer[500];

using namespace std;
int main(int argc, char *argv[], char *envp[])
{
	int err;
	int incX=1,incY=0,incZ=0;
	
	if( argc == 3) // user entered 2 arguments, assume x y increments
	{
		incX=atoi(argv[1]);
		incY=atoi(argv[2]);
	}
	else if( argc == 2) // 1 argument, assume x increment
		incX=atoi(argv[1]);
	else if( argc == 1) // no arguments
		cout <<"No user inputs. Using default increments 1,0,0\n";
	else
	{
		cout << "Invalid Input: incX [incY]\n";
		exit (-3);
	}
	
	cout << "incX=" << incX << "," << "incY=" << incY << "\n";
	cout << "Press Enter to continue:";
	getchar();
	
	
	// Open for read (will fail if file "mission.biedi" does not exist)  
	stream=fopen(missionFile, "r");
	if (stream)
		printf("The file '%s' was opened\n",missionFile);
	else
	{
		printf("The file '%s' was not opened\n", missionFile);
		exit(-1);
	}

	// Open new mission file for write  

	stream2=fopen("data2.biedi", "w");
	if (stream2)
		printf("The file 'data2.biedi' was opened\n");
	else
	{
		printf("The file 'data2.biedi' was not opened\n");
		exit(-2);
	}

	// init the starting x,y,z
	// the center of the box in the mission map
	x = 1000; 
	y = 1000;
	z = 0;
	
	for (i = 0; i < 20000; i++) {
		fgets(aline, 500, stream);
		if (feof(stream))
			break;
		printf("%s", aline);
		if (strstr(aline, "POSITION")) {
			sprintf(buffer, "%s%d,%d,%d]\";", position,x,y,z);
			x += incX;
			y += incY;
			z += incZ;
			printf("%s", buffer);
			fputs(buffer, stream2);
			fputs("\n",stream2);
		}
		else	
			fputs(aline, stream2);
	}

	// Close stream if it is not NULL   
	if (stream)
		err = fclose(stream);
	if (err == 0)
		printf("The file 'mission.biedi' was closed\n");
	else
		printf("The file 'mission.biedi' was not closed\n");

	// Close stream2 if it is not NULL   
	if (stream2)
		err = fclose(stream2);
	if (err == 0)
		printf("The file 'data2.biedi' was closed\n");
	else
		printf("The file 'data2.biedi' was not closed\n");
	
	printf("%d lines processed\nPress Enter to exit:",i);
	getchar();
	
	return (0);
}