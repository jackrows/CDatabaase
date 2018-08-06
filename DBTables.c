/***************************************************
****	Implementation of DB table functions	****
****************************************************/

#include "DBTables.h"

/*Create and initialize the table*/
p_Table DBTableCreation(char* const name, int colSize)
{
	/*Create Table object*/
	p_Table table = malloc(sizeof(Table));
	
	/*Allocate memory for rows. On initialization only one*/
	table->tableValues = malloc(sizeof(char**));
	
	int i;
	for(i = 0; i < colSize; i++)	/*Allocate columns for the row*/
		table->tableValues[i] = malloc(sizeof(char*));
		
	/*Initialize the table with empty string and with specific name*/
	table->tableName = malloc(sizeof(char) * NAMES_LENGTH);
	//table->tableName = name;
	strcpy(table->tableName, name);
	table->columnCount = colSize;
	
	for(i = 0; i < colSize; i++)
		table->tableValues[0][i] = "";
		
	return table;
}
