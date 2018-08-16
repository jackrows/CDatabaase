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
	if(table == NULL || cellName == NULL || newValue == NULL)	//Check tha parameters
	{
		printf("\n#The table, or the name of the cell, or the new value is wrong or empty.\n");
		return -2;
	}
	
	int i, searchCell = -1;		//iterator, keep the possition of willing column
	
	for(i = 0; i < table->columnCount; i++)	//iterate the columns
	{
		if(strcmp(table->columnNames[i], cellName) == 0)	//if the column that user input founded
		{
			searchCell = i;		//Keep the column position
			break;
		}
	}
	
	/*Check if the row number that user input is valid. Must be between 0-table->rowCount.*/
	if(row > table->rowCount - 1)
	{
		printf("\n# You input a row number larger than the total rows of the table.\n");
		return -2;
	}
	
	/*Handle the case that the input column name doesn't founded in table*/
	if(searchCell < 0)
	{
		printf("\n#The cell is not found in table.Please sure that the cell name is right.\n");
		return -1;
	}
	else
	{
		//char* oldValue;
		printf("\n Updated: '%s' -> '%s'\n", table->tableValues[row][searchCell], newValue);
		strcpy(table->tableValues[row][searchCell], newValue);	//copy the value that user input in specific cell
		//printf("\n Updated: '%s' -> '%s'\n", oldValue, table->tableValues[row][searchCell]);
	}
	return searchCell;
}

/*Insert a new recond in the table
* Return -1 if the table is empty, 0 if allocation memory failed and 1 on success*/
int DBInsertRec(p_Table table)
{
	/*if(table == NULL)	//Check if the passed table is empty
	{
		return -1;
	}*/
	int emptyTable = TableEmpty(table);
	if(emptyTable == -1)
	{
		//printf("\n# The table is empty and possible not created.\n");
		return -1;
	}
	//else if(emptyTable == 1)
	//{
		//printf("\n# The table '%s' is empty.\n", table->tableName);
	//	return -1;
	//}
	
	while ((getchar()) != '\n');	//Clear the flush of stdin
	
	char newRecord[1][table->columnCount][40];	//temp record to store the new values to insert in table
	int i,j;
	for(i = 0; i < 1; i++)	//iterate the rows
	{
		char cellValue[40];
		for(j = 0 ; j < table->columnCount; j++)	//iterate the columns
		{
			printf("\n#Please give value for column '%s'\n", table->columnNames[j]);
			//fgets(cellValue, 40, stdin);
			scanf("%[^\n]s", cellValue);
			while ((getchar()) != '\n');	//Clear the flush of stdin
			strcpy(newRecord[i][j], cellValue);		//keep the input from user
		}
	}
	/*If is insertion after the creation, where there is already one empty row(record) and update the empty row*/
	/*int emptyTable = 1;
	if(table->rowCount == 1)
	{
		for(j = 0; j < table->columnCount; j++)
		{
			if(strcmp(table->tableValues[0][j], "") != 0)
			{
				emptyTable = 0;
				break;
			}
		}
	}*/
	if(table->rowCount == 1 && emptyTable == 1)
	{
		for(j = 0; j < table->columnCount; j++)
		{
			strcpy(table->tableValues[0][j], newRecord[0][j]);
		}
		return 1;
	}
	
	char*** tempTable = malloc(sizeof(char**) * (table->rowCount + 1));	//Create temp table object and allocate memory for rows plus 1 of the main table
	if(tempTable == NULL)	//Check the malloc return
		return 0;
		
	for(i = 0; i < table->rowCount; i++)	//iterate rows
	{
		tempTable[i] = malloc(sizeof(char*) * table->columnCount);	//Allocate memory for the columns
		for(j = 0; j < table->columnCount; j++)	//iterate columns
		{
			tempTable[i][j] = malloc(sizeof(char) * 40);		//Allocate memory for the strings
			strcpy(tempTable[i][j], table->tableValues[i][j]);	//copy cell's values from the main table to the temporaly 
		}
	}
	tempTable[table->rowCount] = malloc(sizeof(char*) * table->columnCount);	//Allocate memory for the extra row
	for(j = 0; j < table->columnCount; j++)	//iterate columns
	{
		tempTable[table->rowCount][j] = malloc(sizeof(char) * 40);	//Allocate memory for the strings
		strcpy(tempTable[table->rowCount][j], newRecord[0][j]);		//copy the values of new Record to the temp table
	}
	/*Free memory for the strings, columns and rows of the original table*/
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
	table->rowCount++;			//Increase the row's numbers of the main table by one to insert the new record
	table->tableValues = malloc(sizeof(char**) * table->rowCount);	//Allocate new memory for the rows for the main table with new row number
	if(table->tableValues == NULL)
		return 0;
		
	for(i = 0; i < table->rowCount; i++)	//iterate rows
	{
		table->tableValues[i] = malloc(sizeof(char*) * table->columnCount);	//Allocate memory for the columns
		for(j = 0; j < table->columnCount; j++)		//iterate columns
		{
			table->tableValues[i][j] = malloc(sizeof(char) * 40);	//Allocate memory for the strings
			strcpy(table->tableValues[i][j], tempTable[i][j]);		//copy the cell's values of the temp table to main table
		}
	}
	
	/*Free the allocated memory for the temporaly table*/
	for(i = 0; i < table->rowCount - 1; i++)
	{
		for(j = 0; j < table->columnCount; j++)
		{
			free(tempTable[i][j]);
		}
		free(tempTable[i]);
	}
	free(tempTable);
	//while ((getchar()) != '\n');	//Clear the flush of stdin
	return 1;
}

/*Remove a record from the table
* */
int DBRemoveRec(p_Table table)
{
	/*if(table == NULL || table->rowCount == 0)
		return -2;
		
	int i,j;
	if(table->rowCount == 1)	//Check if the table contains one row and empty strings.
	{
		int emptyTable = 1;
		for(i = 0; i < table->rowCount; i++)
		{	
			for(j = 0; j < table->columnCount; j++)
			{
				if(strcmp(table->tableValues[i][j], "") != 0)
				{
					emptyTable = 0;
					break;
				}
			}
			if(emptyTable == 0)
				break;
		}
		if(emptyTable == 1)
		{
			//printf("\n# The table is empty!\n");
			return -2;
		}
	}*/
	int emptyTable = TableEmpty(table);
	if(emptyTable == -1)
	{
		//printf("\n# The table is empty and possible not created.\n");
		return -2;
	}
	/*else if(emptyTable == 1)
	{
		printf("\n# The table '%s' is empty.\n", table->tableName);
		return -1;
	}*/
	
	int i,j;
	
	printf("\n# Please give the number of row that you want to delete(>0).\n");
	int rowToDelete = -1;
	scanf("%d*d", &rowToDelete);
	if(rowToDelete <= 0)
	{
		printf("\n# You input wrong number. Please verify what row you want to delete.\n");
		return -1;
	}
	if(rowToDelete > table->rowCount)
	{
		printf("\n# You input row number larger than the data in the table.\n");
		return -1;
	}
	
	char*** tempTable = malloc(sizeof(char**) * (table->rowCount - 1));
	if(tempTable == NULL)
		return -2;
	
	int checked = 0;
	for(i = 0; i < table->rowCount - 1; i++)
	{
		if(checked == 0)
			if(i == rowToDelete - 1)	//skip the row that user input
			{
				checked = 1;
				//continue;
			}
		tempTable[i] = malloc(sizeof(char*) * table->columnCount);
		for(j = 0; j < table->columnCount; j++)
		{
			tempTable[i][j] = malloc(sizeof(char) * 40);
			if(checked == 1)
				strcpy(tempTable[i][j], table->tableValues[i+1][j]);
			else
				strcpy(tempTable[i][j], table->tableValues[i][j]);
		}
	}
	
	/*Free memory for the strings, columns and rows of the original table*/
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
	table->rowCount--;
	
	table->tableValues = malloc(sizeof(char**) * table->rowCount);
	for(i = 0; i < table->rowCount; i++)
	{
		table->tableValues[i] = malloc(sizeof(char*) * table->columnCount);
		for(j = 0; j < table->columnCount; j++)
		{
			table->tableValues[i][j] = malloc(sizeof(char) * 40);
			strcpy(table->tableValues[i][j], tempTable[i][j]);
		}
	}
	
	/*Free the allocated memory for the temporaly table*/
	for(i = 0; i < table->rowCount - 1; i++)
	{
		for(j = 0; j < table->columnCount; j++)
		{
			free(tempTable[i][j]);
		}
		free(tempTable[i]);
	}
	free(tempTable);
	while ((getchar()) != '\n');	//Clear the flush of stdin
	return 1;
}

/*Select all the values for a single column
* Display the column by all records. All possible errors handle inside the function*/
void DBSelectColumnByName(const p_Table table)
{
	/*if(table == NULL || table->rowCount == 0)
	{
		printf("\n# The table is empty!\n");
		return;
	}
	else if(table->rowCount == 1)	//Check if the table contains one row and empty strings.
	{
		int i, j, emptyTable = 1;
		for(i = 0; i < table->rowCount; i++)
		{	
			for(j = 0; j < table->columnCount; j++)
			{
				if(strcmp(table->tableValues[i][j], "") != 0)
				{
					emptyTable = 0;
					break;
				}
			}
			if(emptyTable == 0)
				break;
		}
		if(emptyTable == 1)
		{
			printf("\n# The table is empty!\n");
			return;
		}
	}*/
	int emptyTable = TableEmpty(table);
	if(emptyTable == -1)
	{
		printf("\n# The table is empty and possible not created.\n");
		return;
	}
	else if(emptyTable == 1)
	{
		printf("\n# The table '%s' is empty.\n", table->tableName);
		return;
	}
	
	printf("\n# Please give the name of the column.\n");
	char columnName[NAMES_LENGTH];
	scanf("%s*s", columnName);
	
	int findColumn = -1;
	int i;
	
	for(i = 0; i < table->columnCount; i++)
	{
		if(strcmp(table->columnNames[i], columnName) == 0)
		{
			findColumn = i;
			break;
		}
	}
	
	if(findColumn < 0)
	{
		printf("\n# The column you input '%s', doesn't exist in table '%s'.\n", columnName, table->tableName);
		return;
	}
	
	printf("\n---------------------------\n");
	for(i = 0; i < table->rowCount; i++)
	{
		printf(" %d -> %s\n", i+1, table->tableValues[i][findColumn]);
	}
	printf("---------------------------\n");
	return;
}

/*Select one record with specific condition
* Display all columns of the row. All errors handling inside the function*/
void DBSelectRec(const p_Table table)
{
	/*if(table == NULL || table->rowCount == 0)
	{
		printf("\n# The table is empty!\n");
		return;
	}
	else if(table->rowCount == 1)	//Check if the table contains one row and empty strings.
	{
		int i, j, emptyTable = 1;
		for(i = 0; i < table->rowCount; i++)
		{	
			for(j = 0; j < table->columnCount; j++)
			{
				if(strcmp(table->tableValues[i][j], "") != 0)
				{
					emptyTable = 0;
					break;
				}
			}
			if(emptyTable == 0)
				break;
		}
		if(emptyTable == 1)
		{
			printf("\n# The table is empty!\n");
			return;
		}
	}*/
	int emptyTable = TableEmpty(table);
	if(emptyTable == -1)
	{
		printf("\n# The table is empty and possible not created.\n");
		return;
	}
	else if(emptyTable == 1)
	{
		printf("\n# The table '%s' is empty.\n", table->tableName);
		return;
	}	
		
	printf("\n# Please give the name of column to apply the condition.\n");
	char columnName[NAMES_LENGTH];
	scanf("%s*s", columnName);
	while ((getchar()) != '\n');	//Clear the flush of stdin
	printf("\n# Please give the value of the condition.\n");
	char condition[40];
	scanf("%[^\n]s", condition);
	
	int findColumn = -1;
	int i;
	for(i = 0; i < table->columnCount; i++)
	{
		if(strcmp(table->columnNames[i], columnName) == 0)
		{
			findColumn = i;
			break;
		}
	}
	if(findColumn < 0)
	{
		printf("\n# The column you input '%s', doesn't exist in table '%s'.\n", columnName, table->tableName);
		return;
	}
	
	int findCondition = -1;
	for(i = 0; i < table->rowCount; i++)
	{
		if(strcmp(table->tableValues[i][findColumn], condition) == 0)
		{
			findCondition = i;
			break;
		}
	}
	if(findCondition < 0)
	{
		printf("\n# The value for condition you input '%s', doesn't exist in column '%s'\n", condition, columnName);
		return;
	}
	
	printf("\n----------------------------------------------------\n");
	for(i = 0; i < table->columnCount; i++)
	{
		printf("| %s |", table->columnNames[i]);
	}
	printf("\n");
	for(i = 0; i <table->columnCount; i++)
	{
		printf("| %s |", table->tableValues[findCondition][i]);
	}
	printf("\n----------------------------------------------------\n");
	return;
}

/*Display all record of the table
* */
void DBSelectWholeTable(const p_Table table)
{
	/*if(table == NULL)
	{
		printf("\n# The table is empty!\n");
		return;
	}
	
	int i,j;
	if(table->rowCount == 1)	//Check if the table contains one row and empty strings.
	{
		int emptyTable = 1;
		for(i = 0; i < table->rowCount; i++)
		{	
			for(j = 0; j < table->columnCount; j++)
			{
				if(strcmp(table->tableValues[i][j], "") != 0)
				{
					emptyTable = 0;
					break;
				}
			}
			if(emptyTable == 0)
				break;
		}
		if(emptyTable == 1)
		{
			printf("\n# The table is empty!\n");
			return;
		}
	}*/
	int emptyTable = TableEmpty(table);
	if(emptyTable == -1)
	{
		printf("\n# The table is empty and possible not created.\n");
		return;
	}
	else if(emptyTable == 1)
	{
		printf("\n# The table '%s' is empty.\n", table->tableName);
		return;
	}
	
	int i,j;
	printf("\n----------------------------------------------------------\n");
	for(i = 0; i < table->columnCount; i++)
		printf("| %s |", table->columnNames[i]);
	
	printf("\n");
	
	for(i = 0; i < table->rowCount; i++)
	{
		for(j = 0; j < table->columnCount; j++)
		{
			printf("| %s |", table->tableValues[i][j]);
		}
		printf("\n");
	}
	printf("----------------------------------------------------------\n");
}

/*Display records by applied complex condition
* */
void DBSelectRecByComplexCondition(const p_Table table)
{
	/*if(table == NULL || table->rowCount == 0)
	{
		printf("\n# The table is emtpy.\n");
		return;
	}
	int i,j;
	if(table->rowCount == 1)	//Check if the table contains one row and empty strings.
	{
		int emptyTable = 1;
		for(i = 0; i < table->rowCount; i++)
		{	
			for(j = 0; j < table->columnCount; j++)
			{
				if(strcmp(table->tableValues[i][j], "") != 0)
				{
					emptyTable = 0;
					break;
				}
			}
			if(emptyTable == 0)
				break;
		}
		if(emptyTable == 1)
		{
			printf("\n# The table is empty!\n");
			return;
		}
	}*/
	int emptyTable = TableEmpty(table);
	if(emptyTable == -1)
	{
		printf("\n# The table is empty and possible not created.\n");
		return;
	}
	else if(emptyTable == 1)
	{
		printf("\n# The table '%s' is empty.\n", table->tableName);
		return;
	}
	
	int i,j;
	
	char conditionValue[table->columnCount][40];
	char conditionNames[table->columnCount][NAMES_LENGTH];
	for(i = 0; i < table->columnCount; i++)
	{
		while ((getchar()) != '\n');	//Clear the flush of stdin
		printf("\n# Please give the name of column that condition will be applied. To finished with the conditions press enter\n");
		scanf("%[^\n]s", conditionNames[i]);
		if(strcmp(conditionNames[i], "") == 0 || strcmp(conditionNames[i], "\n") == 0 || conditionNames[i] == NULL)
			break;
		while ((getchar()) != '\n');	//Clear the flush of stdin
		printf("\n# Please give the willing value to check for the column '%s'.\n", conditionNames[i]);
		scanf("%[^\n]s", conditionValue[i]);
	}
	
	while ((getchar()) != '\n');	//Clear the flush of stdin
	int conditionCount = i;
	int findColumns[conditionCount];
	for(i = 0; i < conditionCount; i++)
	{
		findColumns[i] = -1;
		//int j;
		for(j = 0; j < table->columnCount; j++)
		{
			if(strcmp(conditionNames[i], table->columnNames[j]) == 0)
			{
				findColumns[i] = j;
				break;
			}
		}
	}
	int allColumnConditionCheck = 1;
	for(i = 0; i < conditionCount; i++)
	{
		if(findColumns[i] == -1)
		{
			allColumnConditionCheck = 0;
			break;
		}
	}
	if(allColumnConditionCheck == 0)
	{
		printf("\n# Doesn't founded all the columns you input. The conditions will applied for the existed columns.\n");
	}
	
	int findConditions[conditionCount];
	int row = -1;
	for(i = 0; i < conditionCount; i++)
	{
		findConditions[i] = -1;
		if(findColumns[i] == -1)
			continue;
		
		//int j;
		for(j = 0; j < table->rowCount; j++)
		{
			if(row != j)
				continue;
				
			if(strcmp(table->tableValues[j][findColumns[i]], conditionValue[i]) == 0)
			{
				findConditions[i] = j;
				row = j;
				break;
			}
		}
	}
	
	/*for(i = 0; i < table->rowCount; i++)
	{
		//int j;
		for(j = 0; j < conditionCount; j++)
		{
			findConditions[j] = -1;
			if(findColumns[j] == -1)
				continue;
			if(strcmp(table->tableValues[i][j], conditionValue[j]) == 0)
			{
				findConditions[j] = j;
			}
		}
	}*/
	
	int allValueConditionCheck = 1;
	for(i = 0; i < conditionCount; i++)
	{
		if(findConditions[i] == -1)
		{
			allValueConditionCheck = 0;
			break;
		}
	}
	if(allValueConditionCheck == 0)
	{
		printf("\n# Not all values for the existes columns found. The condition will be applied for the founded values.\n");
	}
	
	printf("\n----------------------------------------------------\n");
	for(i = 0; i < table->columnCount; i++)
	{
		printf("| %s |", table->columnNames[i]);
	}
	printf("\n");
	for(i = 0; i <table->columnCount; i++)
	{
		if(findColumns[i] != -1 && findConditions[i] != -1)
		{
			printf("| %s |", table->tableValues[findConditions[i]][findColumns[i]]);
		}
	}
	printf("\n----------------------------------------------------\n");
	
	return;
}

/*Check if a table is empty or it is used immediately after the creation where contains one row with empty values
* Return -1 if the table is null, 0 if the table is NOT empty and 1 if the table is empty*/
int TableEmpty(const p_Table table)
{
	if(table == NULL)	//If table is null or created but without rows
	{
		//printf("\n# The table is not created.\n");
		return -1;
	}
	int i,j;
	if(table->rowCount == 0)
	{
		//printf("\n# The table is empty.\n");
		return 1;
	}
	else if(table->rowCount == 1)	//Check if the table contains one row and empty strings.
	{
		int emptyTable = 1;
		for(i = 0; i < table->rowCount; i++)
		{	
			for(j = 0; j < table->columnCount; j++)
			{
				if(strcmp(table->tableValues[i][j], "") != 0)
				{
					emptyTable = 0;
					break;
				}
			}
			if(emptyTable == 0)
				break;
		}
		if(emptyTable == 1)
		{
			//printf("\n# The table is empty!\n");
			return 1;
		}
	}
	return 0;
}
