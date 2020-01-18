#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#define max 2
struct Table
{
	char *entry[max];
	char *status[max];

};
void execute(char *);
sqlite3 *db;
int rc;
char *err_msg = 0;

int main(void) 
{
    struct Table *t=(struct Table*)malloc(sizeof(struct Table));
    rc = sqlite3_open("test.db", &db);
    char *sql[100];
    for(int i=0;i<max;i++)
    {
	t->entry[i]=(char*)malloc(100*sizeof(char));
	t->status[i]=(char*)malloc(100*sizeof(char));
     }
     for(int i=0;i<max;i++)
     {
	scanf("%s %s",t->entry[i],t->status[i]);
	
     }
     /*t->entry[0]="pavithraa";
     t->entry[1]="mithra";
     t->status[0]="success";
     t->status[1]="success";
     */
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    sql[0] =  "DROP TABLE IF EXISTS Sample;" 
              "CREATE TABLE Sample(ENTRY TEXT,STATUS TEXT);" ;
    
    execute(sql[0]);            
    for(int i=1;i<=max;i++)
    {
	sql[i]=(char*)malloc(100*sizeof(char));
	sprintf(sql[i],"INSERT INTO Sample VALUES('%s','%s');",t->entry[i-1],t->status[i-1]);
	execute(sql[i]);
    
    }    
    sqlite3_close(db);
    
    return 0;
}

void execute(char *sql)
{
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) 
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
    } 
}
