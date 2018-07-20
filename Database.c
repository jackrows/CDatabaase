/***********************************************
****	Definition of Database functions	****
************************************************/

#include "Database.h"

/*Creation and initialization of Database table with one row and columns=int argument*/
p_Database DatabaseCreation(char* const dbName, int tablesNumber)
{
	printf("#Initialization of Database and Tables...\n");
	/*Create new database object*/
	p_Database database = malloc(sizeof(Database));
	
	/*Create database tables array*/
	database->tables = malloc(sizeof(Table) * tablesNumber);
	
	/*Initialize database table with empty strings and assign the name*/
	database->dbName = dbName;
	
	int i, colSize = 0;
	char *tableName = malloc(sizeof(char) * NAMES_LENGTH);
	
	/*Create each table and initialize them*/
	for(i = 0; i < tablesNumber; i++)
	{
		printf("\tPlease give a name for the table...\n");
		scanf("%s*s", tableName);
		printf("\tPlease give the number of columns of the table...\n");
		scanf("%d*d", &colSize);
		database->tables[i] = DBTableCreation(tableName, colSize);
	}	
	printf("#Initialization DONE\n");
	return database;
}
