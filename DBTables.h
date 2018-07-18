/*******************************************
****	Header of the tables of DB		****
********************************************/
#ifndef __DB_Tables_H__
#define __DB_Tables_H__

#include <stdio.h>
#include "Database.h"
/*Definition of structure of table*/
typedef struct Table {
	char* 	tableName;			/*Store the name of the table*/
	char***	tableValues			/*2d dimensional array of strings that simulate the real table of DB*/
}Table;

typedef Table* p_Table;			/*Pointer of table structure*/

/*Declaration of functions about DB Tables*/
p_Database 	DBTableCreation(char*, int);					/*Create a table in DB*/
int			DBInsertRec(p_Database);						/*Insert a line in the table*/
int			DBRemoveRec(p_Database);						/*Remove a line from the table*/
int			DBSearchRec(Database);						/*Search for a record in the table*/
char*		DBSelectColumnByName(Database, char*);		/*Select a single column values by column name*/
char* 		DBSelectColumnByNo(Database, int);			/*Select a signle column values by column number sequence(zero-based)*/
Database	DBSelectMultiColsByNames(Database, char*);	/*Select a subtable values by columns names*/
char*		DBSelectRec(Database, char*);					/*Select a line from the table*/

#endif
