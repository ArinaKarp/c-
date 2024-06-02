#include <stdio.h>
#include <sqlite3.h>
#include <string>
 
// int callback(void*, int, char**, char**);
 int callback(void *notUsed, int colCount, char **columns, char **colNames)
{
    for (int i = 0; i < colCount; i++)
    {
        printf("%s = %s\n", colNames[i], columns[i] ? columns[i] : "NULL");
    }
    printf("\n");
    return 0;
}
int main() {
    sqlite3* db;
    char *err_msg = 0;
    int rc  = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return 1;
    }
    const char *sql = "SELECT * FROM test_messages;";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK )
    {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}
 
// int callback(void *notUsed, int colCount, char **columns, char **colNames)
// {
//     for (int i = 0; i < colCount; i++)
//     {
//         printf("%s = %s\n", colNames[i], columns[i] ? columns[i] : "NULL");
//     }
//     printf("\n");
//     return 0;
// }