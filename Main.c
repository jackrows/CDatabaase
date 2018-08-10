/***********************************************
****	Main program that use the Database	****
************************************************/

#include "Database.h"
#include "GeneralFunctions.h"

int main()
{	
	/*Variables*/
	p_Database database = NULL;		/*Database pointer*/
	int tablesNo = 0;				/*Database tables number*/
	char* databaseName = NULL;		/*Database name*/
	int option = 0;					/*Keep the user option*/
	int	ret_scanf = -1;				/*Check the return of scanf for invalid input from the user*/
	
	PrintOptionDatabase();	//Display the available actions over the Database
	
	while( (ret_scanf = scanf("%d*d", &option)) == 1)
	{
		switch (option){
			case 1:
				if(database != NULL)	//Check if database has been created before and let the user to decide to overide it
				{
					printf("# WARNING - The Database %s contains data. Do you want to overwrite them?(y/n)\n", database->dbName);
					char confirm;
					while ((getchar()) != '\n');	//Clear the flush of stdin
					scanf("%c*c", &confirm);
					if(confirm == 'y' || confirm == 'Y')	//If the user confirm to continue with overidded
						;
					else
					{
						PrintOptionDatabase();
						continue;
					}
				}
			
				databaseName = malloc(sizeof(char) * NAMES_LENGTH);	//Allocate memory for the Database name
				
				printf("Please give the name of Database...\n");
				scanf("%s*s", databaseName);
				printf("Please give the number of willing tables(This is not final)...\n");
				scanf("%d*d", &tablesNo);
				
				database = DatabaseCreation(databaseName, tablesNo);	//Create and allocate memory for the Database
				PrintOptionDatabase();
				break;
			case 2:
				if(database == NULL)
				{
					printf("\n# Please first create a Database.\n");
					break;
				}
				int check = DatabaseAddTable(database);
				if(check == 0)	//No error in insert
				{
					;
				}
				else if(check > 0)
				{
					;
				}
				else
				{
					;
				}
				break;
			case 3:
				if(database == NULL)
				{
					printf("\n# Please first create a Database.\n");
					PrintOptionDatabase();
					break;
				}
				break;
			case 4:
				if(database == NULL)
				{
					printf("\n# Please first create a Database.\n");
					PrintOptionDatabase();
					break;
				}
				int searchResult = -1;		//Keep the result of searching
				char* searchName = malloc(sizeof(char) * NAMES_LENGTH);		//Create a string to keep the user table name
				printf("\nPlease give the name of the table to search.\n");
				scanf("%s*s", searchName);
				
				searchResult = DatabaseSearchTable(*database, searchName);	//Search for the table and keep the possition
				
				/*Check the return of searching*/
				if(searchResult == -2)
				{
					printf("\n#The search was impossible because the database or the searching name is empty.\n");
				}
				else if(searchResult >= 0)
					printf("\n# The table '%s' is found in Database.\n", searchName);
				else
					printf("\n# The table '%s' is not found in Database.\n", searchName);
				
				free(searchName);		//Free the local variable for the name table
				PrintOptionDatabase();
				break;
			case 5:
				DatabasePrint(database);	//Print the tables there are in Database
				PrintOptionDatabase();
				break;
			case 6:
				if(database == NULL)
				{
					printf("\n# Please first create a Database.\n");
					PrintOptionDatabase();
					break;
				}
				printf("\n#Please give the name of tha table you want to insert\n");
				char tableName[NAMES_LENGTH];	//local string to keep the table from user input
				scanf("%s*s", tableName);
				
				int searchTable = DatabaseSearchTable(*database, tableName);	//First search for the table in Database
				
				/*Check the return of searching the table in Database*/
				if(searchTable == -2)
				{
					printf("\n#The search was failed, because the Database or the name table is empty.\n");
					PrintOptionDatabase();
					continue;
				}
				else if(searchTable == -1)
				{
					printf("\n#The table '%s' doesn't founded in Database. Please make sure you input the name of table right.\n", tableName);
					PrintOptionDatabase();
					continue;
				}
				
				printf("\n# You are insert in '%s' table.\n", database->tables[searchTable]->tableName);
				PrintOptionTable();		//Display the available actions for the table
				
				int optionTable = 0, ret_scanf_table = 0;	//Store the option of user, keep the result of scanf return
				while((ret_scanf_table = scanf("%d*d", &optionTable)) == 1)
				{
					switch(optionTable){
						case 1:;
							int insertResult = DBInsertRec(database->tables[searchTable]);	//Insert new record by the user and keep the return
							
							/*Check the return of insertion, and handle every result*/
							if(insertResult == -1)
							{
								printf("\n#The table is empty.\n");
							}
							else if(insertResult == 0)
							{
								printf("\n#There was an error in memory.\n");
							}
							else
							{
								printf("\n# The insertion complete successful.\n");
							}
							PrintOptionTable();
							break;
						case 2:
							printf("\n#Removing...\n");
							int removeResult = DBRemoveRec(database->tables[searchTable]);
							if(removeResult == -2)
							{
								printf("\n# The table '%s' is empty.\n", database->tables[searchTable]->tableName);
							}
							else if(removeResult == -1)
							{
								printf("\n# The deleted of row failed.\n");
							}
							else
							{
								printf("\n#Removing...DONE\n");
							}
							PrintOptionTable();
							break;
						case 3:
							DBSelectWholeTable(database->tables[searchTable]);
							PrintOptionTable();
							break;
						case 4:
							DBSelectColumnByName(database->tables[searchTable]);
							PrintOptionTable();
							break;
						case 5:
							DBSelectRec(database->tables[searchTable]);
							PrintOptionTable();
							break;
						case 6:
							PrintOptionTable();
							break;
						case 7:
							printf("\n# Please give the name of the column that you want to change\n");
							char cellName[NAMES_LENGTH];
							scanf("%s*s", cellName);
							printf("# Please give the number of row, that you want to update(>0)\n");
							
							int rowNumber = -1;		//Store the row number that user want to update
							scanf("%d*d", &rowNumber);
							/*Check user's input*/
							if(rowNumber < 0)
							{
								printf("\n# You input wrong number for the row.\n");
								PrintOptionTable();
								break;
							}
							
							printf("# Please input the new value of the cell\n");
							char newValue[40];		//Store in local array the new value of user
							scanf("%s*s", newValue);
							
							int updateCell = -1;	//Store the result of updating
							updateCell = DBTableUpdateCell(database->tables[searchTable], cellName, rowNumber - 1, newValue);	//Update the cell that user specify in specific cell
							
							/*Check the return relult of updating*/
							if(updateCell == -2)
							{
								printf("\n#Update the cell is failed. Please check the values you insert.\n");
							}
							else if(updateCell == -1)
							{
								printf("\n# Update cell value failed, because the column doesn't founded in table.\n");
							}
							else
							{
								printf("\n# Update the cell completed successful.\n");
								//PrintOptionTable();
								//continue;
							}
							PrintOptionTable();
							break;
						default:
							continue;
					}
					if(optionTable == 8)	/*Exit from the loop*/
					{
						printf("\n# You exit from the table '%s'.\n", tableName);
						break;
					}
				}
				PrintOptionDatabase();
				break;
			case 7:;
				int destroy = DatabaseDestruction(database);	//Unallocate the memory and keep the result
				
				/*Check the return result of the destruction*/
				if(destroy == 0)
				{
					printf("#Unallocate memory... DONE\n");
					//continue;
				}
				else
				{
					printf("#The unallocated of memory FAILED\n");
					//continue;
				}
				database = NULL;
				PrintOptionDatabase();
				break;
			case 8:
				printf("# Exiting from the Database.\n");
				break;
			default:
				printf("Please choose one of the available options\n");
				continue;
		}
		if(option == 8)
			break;
	}
	
	if(ret_scanf == 0)
	{
		printf("#The given input was invalid.\n");
		printf("#The Database and the tables will be erased...\n");
		DatabaseDestruction(database);	//Unlaocate the used memory
		printf("#Exiting from the Database.\n");
		return 1;
	}
	
	if(option == 8)
	{
		printf("\n# You have been exit from the database.\n");
		if(database == NULL)
		{
			printf("\n# The Database is deleted.\n");
			printf("\n# Exiting from the program.\n");
			return 0;
		}
		printf("\n# The data you store in database will be deleted...\n");
		int descruction = DatabaseDestruction(database);
		if(descruction != 0)
		{
			printf("\n#Exiting from the program.\n");
			return 1;
		}
		printf("\n\n# Exiting from the program\n");
	}
	
	return 0;
}
