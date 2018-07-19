/***************************************************
****	Implementation of DB table functions	****
****************************************************/

#include "DBTables.h"

/*Create and initialize the table*/
p_Table DBTableCreation(char* const name, int colSize)
{
	p_Table table = malloc(sizeof(Table));
	
	table->tableValues = malloc(sizeof(char**));
	int i;
	for(i = 0; i < colSize; i++)
		table->tableValues[i] = malloc(sizeof(char*));
		
	/*Initialize the table*/
	table->tableName = name;
	for(i = 0; i < colSize; i++)
		table->tableValues[0][i] = "";
		
	return table;
}
