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
	table->rowCount = 1;
	table->tableValues = malloc(sizeof(char**) * table->rowCount);
	
	table->tableValues[0] = malloc(sizeof(char*) * colSize); /*Allocate columns for the row*/
	
	for(i = 0; i < colSize; i++)	/*Allocate memory for the value of the cells(string)*/
		table->tableValues[0][i] = malloc(sizeof(char) * 40);	
		
	/*Initialize the table names and values with empty string and with specific name*/
	table->tableName = malloc(sizeof(char) * NAMES_LENGTH);
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
	/*Free memory of the name*/
	free(table->tableName);
	
	int i,j;
	for(i = 0; i < table->columnCount; i++)		/*Free memory of the column names*/
	{
		if(table->columnNames[i] == NULL)
			continue;
		free(table->columnNames[i]);
	}
	free(table->columnNames);	/*Free memory of the general pointer of column name array*/
	
	for(i = 0; i < table->rowCount; i++)	
	{
		for(j = 0; j < table->columnCount; j++)
		{
			free(table->tableValues[i][j]);		/*Free the memory of cells (strings)*/
		}
		free(table->tableValues[i]);	/*Free the memory of rows*/
	}
	free(table->tableValues);		/*Free the memroy of general pointer of array*/
			
	table->columnCount = 0;
	table->rowCount = 0;
	table->tableName = NULL;
	table->columnNames = NULL;
	table->tableValues = NULL;
	return;
}

/*Update the value of a specific cell.
* The cell is specified by the name.
* Return -2 if one of the arguments is null, -1 if the update failed, and the possition of the column for success*/
int DBTableUpdateCell(p_Table table, char* cellName, int row, char* newValue)
{
	if(table == NULL || cellName == NULL || newValue == NULL)
	{
		printf("\n#The table, or the name of the cell, or the new value is wrong or empty.\n");
		return -2;
	}
	int i, searchCell = -1;
	for(i = 0; i < table->columnCount; i++)
	{
		if(strcmp(table->columnNames[i], cellName) == 0)
		{
			searchCell = i;
			break;
		}
		//searchCell = 0;
	}
	
	//int totalRows = (sizeof(table[0]) / sizeof(Table));
	if(row > table->rowCount - 1)
	{
		printf("\n# You input a row number larger than the total rows of the table.\n");
		return -2;
	}
	
	if(searchCell < 0)
	{
		printf("\n#The cell is not found in table.Please sure that the cell name is right.\n");
		return -1;
	}
	else
	{
		strcpy(table->tableValues[row][searchCell], newValue);
	}
	return searchCell;
}

/*Insert a new recond in the table
* Return -1 if the table is empty, 0 if allocation memory failed and 1 on success*/
int DBInsertRec(p_Table table)
{
	if(table == NULL)
	{
		return -1;
	}
	char newLine[1][table->columnCount][40];
	int i,j;
	for(i = 0; i < 1; i++)
	{
		char cellValue[40];
		for(j = 0 ; j < table->columnCount; j++)
		{
			printf("\n#Please give value for column '%s'\n", table->columnNames[j]);
			scanf("%s*s", cellValue);
			strcpy(newLine[i][j], cellValue);
		}
	}
	if(table->rowCount == 1 && (strcmp(table->tableValues[0][0], "") == 0) && (strcmp(table->tableValues[0][1], "") == 0))
	{
		for(i = 0; i < table->rowCount; i++)
		{
			for(j = 0; j < table->columnCount; j++)
			{
				strcpy(table->tableValues[i][j], newLine[i][j]);
			}
		}
		return 1;
	}
	char*** tempTable = malloc(sizeof(char**) * (table->rowCount + 1));
	if(tempTable == NULL)
		return 0;
	for(i = 0; i < table->rowCount; i++)
	{
		tempTable[i] = malloc(sizeof(char*) * table->columnCount);
		for(j = 0; j < table->columnCount; j++)
		{
			tempTable[i][j] = malloc(sizeof(char) * 40);
			strcpy(tempTable[i][j], table->tableValues[i][j]);
		}
	}
	tempTable[table->rowCount] = malloc(sizeof(char*) * table->columnCount);
	for(j = 0; j < table->columnCount; j++)
	{
		tempTable[table->rowCount][j] = malloc(sizeof(char) * 40);
		strcpy(tempTable[table->rowCount][j], newLine[0][j]);
	}
	for(i = 0; i < table->rowCount; i++)
	{
		for(j = 0; j < table->columnCount; j++)
		{
			free(table->tableValues[i][j]);
		}
		free(table->tableValues[i]);
	}
	free(table->tableValues);
	
	table->tableValues = NULL;
	table->rowCount++;
	table->tableValues = malloc(sizeof(char**) * table->rowCount);
	if(table->tableValues == NULL)
		return 0;
	for(i = 0; i < table->rowCount; i++)
	{
		table->tableValues[i] = malloc(sizeof(char*) * table->columnCount);
		for(j = 0; j < table->columnCount; j++)
		{
			table->tableValues[i][j] = malloc(sizeof(char) * 40);
			/*if(i == table->rowCount -1)
			{
				strcpy(table->tableValues[i][j], newLine[i][j]);
				continue;	
			}*/
			strcpy(table->tableValues[i][j], tempTable[i][j]);
		}
	}
	
	for(i = 0; i < table->rowCount - 1; i++)
	{
		for(j = 0; j < table->columnCount; j++)
		{
			free(tempTable[i][j]);
		}
		free(tempTable[i]);
	}
	free(tempTable);
	return 1;
}
