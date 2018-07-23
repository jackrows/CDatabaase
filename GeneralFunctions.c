/***************************************************
****	Implementation of General Functions		****
****************************************************/

#include "GeneralFunctions.h"

/*Display the available options on Database for the user*/
void PrintOptionDatabase()
{
	printf("\nPlease choose your action for the Database:\n");
	printf(" 1 - Create Database\n");
	printf(" 2 - Add Table in Database\n");
	printf(" 3 - Remove Table from Database\n");
	printf(" 4 - Search for a Table in Database\n");
	printf(" 5 - Print Database Schema\n");
	printf(" 6 - Enter to a table\n");
	printf(" 7 - Destroy Database\n");
	printf(" 8 - Exit\n");
	printf("\n");
}

/*Display the available options on Database Table for the user*/
void PrintOptionTable()
{
	printf("\nPlease choose your action for the Table:\n");
	printf(" 1 - Insert Record\n");
	printf(" 2 - Remove Record\n");
	printf(" 3 - Search a specific value\n");
	printf(" 4 - Select a single column\n");
	printf(" 5 - Select all columns for a record\n");
	printf(" 6 - Update a single cell\n");
}
