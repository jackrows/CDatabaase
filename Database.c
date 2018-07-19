/***********************************************
****	Definition of Database functions	****
************************************************/

#include "Database.h"

/*Creation and initialization of Database table with one row and columns=argument*/
p_Database DatabaseCreation(char* const dbName, int tablesNumber)
{
	/*Create new database object*/
	p_Database database = malloc(sizeof(Database));
	
	/*Create database tables array*/
	database->tables = malloc(sizeof(Table) * tablesNumber);
	
	/*Initialize database table with empty strings and assign the name*/
	database->dbName = dbName;
	int i;
	for(i = 0; i < tablesNumber; i++)
		database->tables[i] = DBTableCreation(tableName, colSize);
	
	return database;
}
