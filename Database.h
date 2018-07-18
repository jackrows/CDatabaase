#ifndef __Database_H__
#define __Database_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Definition of Database structure*/
typedef struct Database{
	char **table;		/*2 dimencial table of Database*/
}Database;

typedef Database* p_Database;	/*pointer of Database structure*/

/*Declaration of functions about Database*/
p_Database 	DatabaseTableCreation();							/*Create a table in Database*/
int			DatabaseInsertRec(p_Database);						/*Insert a line in the table*/
int			DatabaseRemoveRec(p_Database);						/*Remove a line from the table*/
int			DatabaseSearchRec(Database);						/*Search for a record in the table*/
char*		DatabaseSelectColumnByName(Database, char*)			/*Select a single column values by column name*/
char* 		DatabaseSelectColumnByNo(Database, int);			/*Select a signle column values by column number sequence(zero-based)*/
Database	DatabaseSelectMultiColsByNames(Database, char*);	/*Select a subtable values by columns names*/
char*		DatabaseSelectRec(Database, char*);					/*Select a line from the table*/

#endif
