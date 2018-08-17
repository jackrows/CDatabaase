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
	database->tablesCount = tablesNumber;
	/*Create database tables array*/
	database->tables = malloc(sizeof(p_Table) * tablesNumber);
	if(database->tables == NULL)
	{
		printf("#ERROR - in creation of Tables.\n");
		return NULL;
	}
	
	/*Initialize database table with empty strings and assign the name*/
	database->dbName = malloc(sizeof(char) * NAMES_LENGTH);
	//database->dbName = dbName;
	strcpy(database->dbName, dbName);
	
	int i, colSize = 0;
	
	if(database->dbName == NULL)
	{
		printf("#ERROR - in allocated memory.\n");
		return NULL;
	}
	
	/*Create each table and initialize them*/
	for(i = 0; i < tablesNumber; i++)
	{
		char *tableName = malloc(sizeof(char) * NAMES_LENGTH);
		printf("\tPlease give a name for the table...\n");
		scanf("%s*s", tableName);
		printf("\tPlease give the number of columns of the table...\n");
		scanf("%d*d", &colSize);
		
		database->tables[i] = DBTableCreation(tableName, colSize);
	}	
	//database->tables[tablesNumber + 1] = NULL;
	printf("#Initialization DONE\n");
	
	return database;
}

/*Insert a table in already created Database.
* Return 0 in success, 1 in error and -1 if database is null*/
int	DatabaseAddTable(p_Database p_db)
{
	if(p_db == NULL)
		return -1;
		
	int 	columns = 0;		//Store the columns number of user input
	char* 	newTableName = malloc(sizeof(char) * NAMES_LENGTH);		//Store the table name of user input
	
	p_Table* tempTables = malloc(sizeof(p_Table) * p_db->tablesCount);	//Temporaliry array of tables to keep the original

	if(tempTables == NULL)	/*Check the temporaliry array*/
		return 1;
	
	int i;
	printf("\n------------------------------------------------------");
	printf("\n# Adding new table...\n");
	//Copy the table of database to temporaliry
	for(i = 0; i < p_db->tablesCount; i++)
	{
		tempTables[i] = malloc(sizeof(Table));
		tempTables[i]->columnCount = p_db->tables[i]->columnCount;
		tempTables[i]->columnNames = malloc(sizeof(char*) * tempTables[i]->columnCount);
		int j;
		for(j = 0; j < tempTables[i]->columnCount; j++)
		{
			tempTables[i]->columnNames[j] = malloc(sizeof(char) * NAMES_LENGTH);
			strcpy(tempTables[i]->columnNames[j], p_db->tables[i]->columnNames[j]);
		}
		
		tempTables[i]->tableName = malloc(sizeof(char) * NAMES_LENGTH);
		strcpy(tempTables[i]->tableName, p_db->tables[i]->tableName);
		
		tempTables[i]->rowCount = p_db->tables[i]->rowCount;
		
		tempTables[i]->tableValues = malloc(sizeof(char**) * tempTables[i]->rowCount);
		for(j = 0; j < tempTables[i]->rowCount; j++)
		{
			tempTables[i]->tableValues[j] = malloc(sizeof(char*) * tempTables[i]->columnCount);
			int k;
			for(k = 0; k < tempTables[i]->columnCount; k++)
			{
				tempTables[i]->tableValues[j][k] = malloc(sizeof(char) * 40);
				strcpy(tempTables[i]->tableValues[j][k], p_db->tables[i]->tableValues[j][k]);
			}
		}
	}
	//Allocate necessary memory for the temp table
	p_db->tablesCount++;
	p_db->tables = realloc(p_db->tables, p_db->tablesCount);
	if(p_db->tables == NULL)
	{
		printf("\n# Realloc failed.\n");
		return 1;
	}
	//p_db->tables[p_db->tablesCount - 1] = DBTableCreation(newTableName, columns);
	//Copy from the temp table array to database array
	for(i = 0; i < p_db->tablesCount; i++)
	{
		if(i == p_db->tablesCount - 1)
		{
			printf("\tPlease give a name for the new table...\n");
			scanf("%s*s", newTableName);
			printf("\tPlease give the number of columns of the table...\n");
			scanf("%d*d", &columns);
			p_db->tables[i] = DBTableCreation(newTableName, columns);
			break;
		}
		p_db->tables[i] = tempTables[i];
	}
	printf("\n# Adding new table...DONE\n");
	//for(i = 0; i < p_db->tablesCount - 1; i++)
	//	DBTableDestructor(tempTables[i]);
	printf("------------------------------------------------------\n");
	return 0;
}

/*Destroy and unallocate the memory of Database and tables*/
int DatabaseDestruction(p_Database db)
{
	if(db == NULL)
		return -1;
	
	int i;
	printf("\n#Free the located memory for tables and Database...\n");
	
	for(i = 0; i < db->tablesCount; i++)	/*Free the memory for each table*/
	{
		DBTableDestructor(db->tables[i]);
	}
	free(db->tables);	/*Free the memory of the outer pointer*/
	free(db->dbName);	/*Free the memory of the database name*/
	free(db);			/*Free the memory of the whole database*/
	db->tables = NULL;
	db->dbName = NULL;
	db->tablesCount = 0;
	db = NULL;
	printf("#Free the memory...DONE\n");
	return 0;
}

/*Search a table in Database through the name
* Return -2 in if Database is empty, the possition of the table if the table founded and -1 not founded*/
int DatabaseSearchTable(Database db, char* searchName)
{
	if(db.dbName == NULL || searchName == NULL)
	{
		printf("\n# The Database or the searching name is empty.\n");
		return -2;
	}
	
	int i;
	for(i = 0; i < db.tablesCount; i++)
	{
		if(strcmp(db.tables[i]->tableName, searchName) == 0)
			return i;
	}
	return -1;
}

/*Display the name and the table array of Database*/
void DatabasePrint(const p_Database db)
{
	if(db == NULL)
	{
		printf("\n#The Database is empty. Please Create one first\n");
		return;
	}
	printf("\n-----------------------------------------\n");
	printf("\tSchema Browser of %s\n", db->dbName);
	printf("-----------------------------------------\n");
	
	int i;
	for(i = 0; i < db->tablesCount; i++)
		printf(" - %s\n", db->tables[i]->tableName);
		
}
