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
	if(database == NULL)
	{
		printf("#ERROR - in creation of Database.\n");
		return NULL;
	}
	
	/*Create database tables array*/
	database->tables = malloc(sizeof(p_Table) * tablesNumber);
	if(database->tables == NULL)
	{
		printf("#ERROR - in creation of Tables.\n");
		return NULL;
	}
	
	/*Initialize database table with empty strings and assign the name*/
	database->dbName = malloc(sizeof(char) * NAMES_LENGTH);
	database->dbName = dbName;
	
	int i, colSize = 0;
	char *tableName = malloc(sizeof(char) * NAMES_LENGTH);
	if(tableName == NULL || database->dbName == NULL)
	{
		printf("#ERROR - in allocated memory.\n");
		return NULL;
	}
	
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

/*Display the name and the table array of Database*/
void DatabasePrint(Database db)
{
	printf("\n-----------------------------------------\n");
	printf("\tSchema Browser of %s\n", db.dbName);
	printf("-----------------------------------------\n");
	
	p_Table pIndex = NULL;
	int i;
	for(i = 0; i < 3; i++)
		printf(" - %s\n", db.tables[i]->tableName);
	
	for(pIndex = db.tables[0]; ; pIndex++)
	{
		printf(" - %s\n", pIndex->tableName);
	}
}
