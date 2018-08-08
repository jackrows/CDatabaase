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
	
	PrintOptionDatabase();
	
	while( (ret_scanf = scanf("%d*d", &option)) == 1)
	{
		switch (option){
			case 1:
				if(database != NULL)
				{
					printf("# WARNING - The Database %s contains data. Do you want to overwrite them?(y/n)\n", database->dbName);
					char confirm;
					while ((getchar()) != '\n');
					scanf("%c*c", &confirm);
					if(confirm == 'y' || confirm == 'Y')
						;
					else
					{
						PrintOptionDatabase();
						continue;
					}
				}
				databaseName = malloc(sizeof(char) * NAMES_LENGTH);
				printf("Please give the name of Database...\n");
				scanf("%s*s", databaseName);
				printf("Please give the number of willing tables(This is not final)...\n");
				scanf("%d*d", &tablesNo);
				database = DatabaseCreation(databaseName, tablesNo);
				PrintOptionDatabase();
				break;
			case 2:;
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
				break;
			case 4:;
				int searchResult = -1;
				char* searchName = malloc(sizeof(char) * NAMES_LENGTH);
				printf("\nPlease give the name of the table to search.\n");
				scanf("%s*s", searchName);
				searchResult = DatabaseSearchTable(*database, searchName);
				if(searchResult == -2)
				{
					printf("\n#The search was impossible because the database or the searching name is empty.\n");
				}
				else if(searchResult >= 0)
					printf("\n# The table '%s' is found in Database.\n", searchName);
				else
					printf("\n# The table '%s' is not found in Database.\n", searchName);
					
				PrintOptionDatabase();
				break;
			case 5:
				DatabasePrint(database);
				PrintOptionDatabase();
				break;
			case 6:
				printf("\n#Please give the name of tha table you want to insert\n");
				char tableName[NAMES_LENGTH];
				scanf("%s*s", tableName);
				
				int searchTable = DatabaseSearchTable(*database, tableName);
				
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
				PrintOptionTable();
				int optionTable = 0, ret_scanf_table = 0;
				while((ret_scanf_table = scanf("%d*d", &optionTable)) == 1)
				{
					switch(optionTable){
						case 1:;
							int insertResult = DBInsertRec(database->tables[searchTable]);
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
							break;
						case 3:
							break;
						case 4:
							break;
						case 5:
							break;
						case 6:
							printf("\n# Please give the name of the column that you want to change\n");
							char cellName[NAMES_LENGTH];
							scanf("%s*s", cellName);
							printf("# Please give the number of row, that you want to update(>0)\n");
							int rowNumber = -1;
							scanf("%d*d", &rowNumber);
							if(rowNumber < 0)
							{
								printf("\n# You input wrong number for the row.\n");
								PrintOptionTable();
								break;
							}
							printf("# Please input the new value of the cell\n");
							char newValue[40];
							scanf("%s*s", newValue);
							
							int updateCell = -1;
							updateCell = DBTableUpdateCell(database->tables[searchTable], cellName, rowNumber - 1, newValue);
							
							if(updateCell == -2)
							{
								printf("\n#Update the cell is failed. Please check the values you insert.\n");
								//break;
							}
							else if(updateCell == -1)
							{
								printf("\n# Update cell value failed, because the column doesn't founded in table.\n");
								//break;
							}
							else
							{
								printf("\n# Update the cell completed successful.\n");
								PrintOptionTable();
								continue;
							}
							PrintOptionTable();
							break;
						case 7:
							break;
						default:
							continue;
					}
					if(optionTable == 7)	/*Exit from the loop*/
					{
						break;
					}
				}
				PrintOptionDatabase();
				break;
			case 7:;
				int destroy = DatabaseDestruction(database);
				if(destroy == 0)
				{
					printf("#Unallocate memory... DONE\n");
					continue;
				}
				else
				{
					printf("#The unallocated of memory FAILED\n");
					continue;
				}
				PrintOptionDatabase();
				break;
			case 8:
				printf("Exiting from the Database.\n");
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
		printf("\n# The data you store in database will be deleted...\n");
		int descruction = DatabaseDestruction(database);
		if(descruction != 0)
		{
			printf("\n#Immediately exit from the program.\n");
			return 1;
		}
	}
	
	return 0;
}
