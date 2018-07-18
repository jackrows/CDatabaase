/***********************************************
****	Main program that use the Database	****
************************************************/

#include "Database.h"

int main()
{
	int 	colSize = 0;
	printf("Please input the  number of columns...\n");
	scanf("%d*d",&colSize);
	
	p_Database database = DatabaseTableCreation("products", colSize);
	
	int i = 0;
	printf("---- %s ----\n", database->tableName);
	for(i = 0; i < colSize; i++)
	{
		printf("[0][%d] = %s\n",i,database->table[0][i]);
	}
	
	return 0;
}
