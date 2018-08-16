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
		
	int 	columns = 0;
	char* 	newTableName = malloc(sizeof(char) * NAMES_LENGTH);
	printf("\tPlease give a name for the new table...\n");
	scanf("%s*s", newTableName);
	printf("\tPlease give the number of columns of the table...\n");
	scanf("%d*d", &columns);
	
	p_Table newTable = DBTableCreation(newTableName, columns);
	p_Table* tempTables = malloc(sizeof(p_Table) * (p_db->tablesCount + 1));

	if(tempTables == NULL || newTable == NULL)
		return 1;
	
	int i;
	//Allocate necessary memory for the temp table
	
	//Copy the table of database to temporaliry
	
	
	for(i = 0; i < p_db->tablesCount; i++)
	{
		DBTableDestructor(p_db->tables[i]);
	}
	free(p_db->tables);
	p_db->tables = NULL;
	
	p_db->tablesCount++;
	p_db->tables = malloc(sizeof(p_Table) * p_db->tablesCount);
	if(p_db->tables == NULL)
	{
		printf("\n# ERROR in creation extra space for the new table.\n");
		return 1;
	}
	for(i = 0; i < p_db->tablesCount; i++)
	{
		p_db->tables[i] = DBTableCreation()
	}
	
	free(newTableName);

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
