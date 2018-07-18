/***********************************************
****	Definition of Database functions	****
************************************************/

#include "Database.h"

/*Creation and initialization of Database table with one row and columns=argument*/
p_Database DatabaseTableCreation(char* name, int colSize)
{
	/*Create new database object*/
	p_Database database = malloc(sizeof(Database));
	
	/*Create new database table*/
	database->table = malloc(sizeof(char**));
	database->table[0] = malloc(sizeof(char*) * colSize);
	
	/*Initialize database table with empty strings and assign the name*/
	database->tableName = name;
	int i;
	for(i = 0; i < colSize; i++)
		database->table[0][i] = " ";
	
	return database;
}

int DatabaseInsertRec(p_Database db)
{
	return 0;
}

int DatabaseRemoveRec(p_Database d)
{
	return 0;
}

int DatabaseSearchRec(Database d)
{
	return 0;
}

char* DatabaseSelectColumnByName(Database d, char* s)
{
	return s;
}
