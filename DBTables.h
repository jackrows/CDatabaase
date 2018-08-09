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
	char* 		tableName;			/*Store the name of the table*/
	char**		columnNames;		/*Array with columns names*/
	short int	columnCount;		/*Store the number of columns for each table*/
	int			rowCount;			/*Store the number of rows for the table*/
	char***		tableValues;		/*2d dimensional array of strings that simulate the real table of DB*/
}Table;

typedef Table* p_Table;			/*Pointer of table structure*/

/*Declaration of functions about DB Tables*/
p_Table 	DBTableCreation(char*, int);				/*Create a table in DB*/
int			DBInsertRec(p_Table);						/*Insert a line in the table*/
int			DBRemoveRec(p_Table);						/*Remove a line from the table*/
int			DBSearchValue(p_Table, char*);					/*Search for a value in the table*/
void		DBSelectColumnByName(const p_Table);			/*Select a single column values by column name*/
void 		DBSelectWholeTable(const p_Table);			/*Select a signle column values by column number sequence(zero-based)*/
Table		DBSelectMultiColsByNames(const p_Table, char*);		/*Select a subtable values by columns names*/
void		DBSelectRec(const p_Table);					/*Select a line from the table*/
int			DBTableUpdateCell(p_Table, char*, int, char*);		/*Update a specific cell of the table*/
void		DBTableDestructor(p_Table);							/*Free the located memory for the table*/

#endif
