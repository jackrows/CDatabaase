/***************************************************
****	Implementation of DB table functions	****
****************************************************/

#include "DBTables.h"

/*Create and initialize the table*/
p_Table DBTableCreation(char* const name, int colSize)
{
	/*Create Table object*/
	p_Table table = malloc(sizeof(Table));
	
	int i;
	/*Allocate memory for the column names*/
	table->columnNames = malloc(sizeof(char*) * colSize);
	for(i = 0; i < colSize; i++)
		table->columnNames[i] = malloc(sizeof(char) * NAMES_LENGTH);
		
	/*Fill in the column names by the user*/
	char colName[NAMES_LENGTH];
	for(i = 0; i < colSize; i++)
	{
		if(i == 0)
			printf("\n\t\tGive the name of the %dst column\n", i+1);
		else if(i == 1)
			printf("\n\t\tGive the name of the %dnd column\n", i+1);
		else
			printf("\n\t\tGive the name of the %dth column\n", i+1);
		
		scanf("%s*s", colName);
		strcpy(table->columnNames[i], colName);
	}
	
	/*Allocate memory for rows. On initialization only one*/
	table->tableValues = malloc(sizeof(char**));
	
	table->tableValues[0] = malloc(sizeof(char*) * colSize); /*Allocate columns for the row*/
	
	//for(i = 0; i < colSize; i++)	/*Allocate columns for the row*/
		//table->tableValues[i] = malloc(sizeof(char*));
	
	for(i = 0; i < colSize; i++)
		table->tableValues[0][i] = malloc(sizeof(char) * 40);	
		
	/*Initialize the table names and values with empty string and with specific name*/
	table->tableName = malloc(sizeof(char) * NAMES_LENGTH);
	//table->tableName = name;
	strcpy(table->tableName, name);
	table->columnCount = colSize;
	
	for(i = 0; i < colSize; i++)
	{
		strcpy(table->tableValues[0][i], "");
	}
	
	return table;
}

/*Free the located memory for the table*/
void DBTableDestructor(p_Table table)
{
	if(table == NULL)
	{
		printf("#The table is empty already.\n");
		return ;
	}
	
	free(table->tableName);
	/*int i;
	for(i = 0; i < table->columnCount; i++)
	{
		if(table->tableValues[i] == NULL)
			continue;
		free(table->tableValues[i]);
	}*/
	free(table->tableValues);
	table->columnCount = 0;
	table->tableName = NULL;
	table->tableValues = NULL;
	return;
}
