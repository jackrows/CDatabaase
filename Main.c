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
				databaseName = malloc(sizeof(char) * NAMES_LENGTH);
				printf("Please give the name of Database...\n");
				scanf("%s*s", databaseName);
				printf("Please give the number of willing tables(This is not final)...\n");
				scanf("%d*d", &tablesNo);
				database = DatabaseCreation(databaseName, tablesNo);
				PrintOptionDatabase();
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
				break;
			case 7:
				printf("Exiting from the Database.\n");
				break;
			default:
				printf("Please choose one of the available options\n");
				continue;
		}
		if(option == 7)
			break;
	}
	
	database->tables[0]->tableValues[0][0] = "Alex";
	printf("%s  %s\n", database->tables[0]->tableValues[0][0], database->tables[0]->tableValues[0][1]);
	
	
	return 0;
}
