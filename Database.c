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
		//database->tables[i] = malloc(sizeof(Table));
		printf("\tPlease give a name for the table...\n");
		scanf("%s*s", tableName);
		printf("\tPlease give the number of columns of the table...\n");
		scanf("%d*d", &colSize);
		database->tables[i] = DBTableCreation(tableName, colSize);
	}	
	database->tables[tablesNumber + 1] = NULL;
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
	printf("\tPlease give a name for the table...\n");
	scanf("%s*s", newTableName);
	printf("\tPlease give the number of columns of the table...\n");
	scanf("%d*d", &columns);
	p_Table newTable = DBTableCreation(newTableName, columns);
	p_Table* tempTables = malloc(sizeof(p_Table) * (p_db->tablesCount + 1));

	if(tempTables == NULL || newTable == NULL)
		return 1;
	
	return 0;
}

/*Destroy and unallocate the memory of Database and tables*/
int DatabaseDestruction(p_Database db)
{
	if(db == NULL)
		return -1;
	
	int i,j;
	printf("/n#Free the located memory for tables and Database...\n");
	
	for(i = 0; i < db->tablesCount; i++)
	{
		DBTableDestructor(db->tables[i]);
	}
	
	free(db->dbName);
	free(db);
	db->dbName = NULL;
	db = NULL;
	db->tablesCount = 0;
	return 0;
}

/*Search a table in Database through the name
* Return -1 in if Database is empty, 1 if the table founded and 0 not founded*/
int DatabaseSearchTable(Database db, char* searchName)
{
	if(db.dbName == NULL || searchName == NULL)
	{
		printf("\n# The Database or the searching name is empty.\n");
		return -1;
	}
	
	int i;
	for(i = 0; i < db.tablesCount; i++)
	{
		if(strcmp(db.tables[i]->tableName, searchName) == 0)
			return 1;
	}
	return 0;
}

/*Display the name and the table array of Database*/
void DatabasePrint(Database db)
{
	if(db.dbName == NULL)
	{
		printf("\n#The Database is empty. Please Create one first\n");
		return;
	}
	printf("\n-----------------------------------------\n");
	printf("\tSchema Browser of %s\n", db.dbName);
	printf("-----------------------------------------\n");
	
	int i;
	for(i = 0; i < db.tablesCount; i++)
		printf(" - %s\n", db.tables[i]->tableName);
		
}
