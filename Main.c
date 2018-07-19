/***********************************************
****	Main program that use the Database	****
************************************************/

#include "Database.h"

int main()
{
	int tablesNo = 0;
	char* databaseName = malloc(sizeof(char) * NAMES_LENGTH);
	printf("Please give the name of Database...\n");
	scanf("%s*s", &databaseName);
	printf("Please give the number of willing table...\n");
	scanf("%d*d", &tablesNo);
	
	p_Database database = DatabaseCreation(databaseName, tablesNo);
	
	return 0;
}
