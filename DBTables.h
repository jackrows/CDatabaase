/*******************************************
****	Header of the tables of DB		****
********************************************/
#ifndef __DB_Tables_H__
#define __DB_Tables_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	NAMES_LENGTH 20

/*Definition of structure of table*/
typedef struct Table {
	char* 	tableName;			/*Store the name of the table*/
	char***	tableValues;		/*2d dimensional array of strings that simulate the real table of DB*/
}Table;

typedef Table* p_Table;			/*Pointer of table structure*/

/*Declaration of functions about DB Tables*/
p_Table 	DBTableCreation(char*, int);				/*Create a table in DB*/
int			DBInsertRec(p_Table, char*);						/*Insert a line in the table*/
int			DBRemoveRec(p_Table, char*);						/*Remove a line from the table*/
int			DBSearchRec(p_Table, char*);						/*Search for a record in the table*/
char*		DBSelectColumnByName(Table, char*);			/*Select a single column values by column name*/
char* 		DBSelectColumnByIndex(Table, int);			/*Select a signle column values by column number sequence(zero-based)*/
Table		DBSelectMultiColsByNames(Table, char*);		/*Select a subtable values by columns names*/
char*		DBSelectRec(Table, char*);					/*Select a line from the table*/
int			DBTableUpdateCell(p_Table, int, int, char*);			/*Update a specific cell of the table*/

#endif
