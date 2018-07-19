/****************************************
***		Header file of Database		*****
*****************************************/
#ifndef __Database_H__
#define __Database_H__

#include "DBTables.h"
#define	NAMES_LENGTH 20
/*Definition of Database structure*/
typedef struct Database{
	char*	dbName;		/*Store the name of the database*/
	p_Table *tables;	/*a array of Tables in Database*/
}Database;

typedef Database* p_Database;	/*pointer of Database structure*/
//int		stringSize = 15;		/*variable that allocate space for strings in table*/

/*Declaration of functions about Database*/
p_Database 	DatabaseCreation(char* const, int);							/*Create a table in Database*/
int			DatabaseAddTable(p_Database, Table);						/*Insert a table in the Database*/
int			DatabaseRemoveTable(p_Database, Table);						/*Remove a table from the Database*/
int			DatabaseSearchTable(Database, Table);						/*Search for a table by the name in the Database*/
int			DatabaseDestruction(p_Database);							/*Destroy and free the memory of Database*/

#endif
