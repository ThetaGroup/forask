#define DB_FILE "/etc/forask/forask.db"
#define TASK_STATE_ACTIVE "00"
#define TASK_STATE_DONE "50"
#define TASK_STATE_ACTIVE_STRING "ACTIVE"
#define TASK_STATE_DONE_STRING "DONE"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"
#include "sqlite3.h"
#include "sql.h"
#include "log.h"

sqlite3 *conn;

void openDb(){
	LOG("Opening local DB...\n");
        int ret=sqlite3_open(DB_FILE,&conn);
        if (ret!=SQLITE_OK){
                LOG("Open local DB failed...\n");
                exit(-1);
        }else{
		LOG("Open local DB successfully...\n");
		char *errMsg;
		ret=sqlite3_exec(
			conn,
			CREATE_CONFIG_TABLE_SQL,
			NULL,
			NULL,
			&errMsg
		);
		if (ret!=SQLITE_OK)
			LOG("%s\n",errMsg);
		if (ret==SQLITE_OK){
			ret=sqlite3_exec(
				conn,
				INSERT_CURRENT_AREA_CONFIG_SQL,
				NULL,
				NULL,
				&errMsg
			);
			if (ret!=SQLITE_OK)
				LOG("%s\n",errMsg);
		}		
		ret=sqlite3_exec(
			conn,
			CREATE_AREA_TABLE_SQL,
			NULL,
			NULL,
			&errMsg
		);
		if (ret!=SQLITE_OK)
			LOG("%s\n",errMsg);
		ret=sqlite3_exec(
			conn,
			CREATE_TASK_TABLE_SQL,
			NULL,
			NULL,
			&errMsg
			);
		if (ret!=SQLITE_OK)
			LOG("%s\n",errMsg);
	}
}

void closeDb(){
	LOG("Closing local DB...\n");
        int ret=sqlite3_close(conn);
        if (ret!=SQLITE_OK){
                LOG("Close loacl DB failed...\n");
                exit(-1);
        }else{
		LOG("Closed local DB successfully...\n");
	}
}

int sync(){
	return 0;
}

int areaShow(){
	openDb();
	char *errMsg;
	char **dbResult;
	int nRow,nColumn;
	
	int ret=sqlite3_get_table(
			conn,
			QUERY_ALL_AREA_SQL,
			&dbResult,
			&nRow,
			&nColumn,
			&errMsg
		);
	if (ret==SQLITE_OK){
		printf("%d areas in total:\n",nRow);
		for (int i=0;i<nRow;i++){
			printf("%s\n",dbResult[(i+1)*nColumn]);
		}
	}else{
		printf("Query all areas failed...\n");
	}

	ret=sqlite3_get_table(
			conn,
			QUERY_CURRENT_AREA_SQL,
			&dbResult,
			&nRow,
			&nColumn,
			&errMsg
		);
	if (ret==SQLITE_OK){
		if (dbResult[1]==NULL){
			printf("No selected area.\n");
		}else{
			printf("Selected area:%s\n",dbResult[1]);
		}
	}


	closeDb();
	return 0;
}

int areaSwitch(char *area){
	openDb();
	char **dbResult;
	int nRow,nColumn;
	char *errMsg;
	char *selectSql=(char*)malloc(1024);
	sprintf(selectSql,QUERY_CERTAIN_AREA_SQL,area);
	int ret=sqlite3_get_table(
			conn,
			selectSql,
			&dbResult,
			&nRow,
			&nColumn,
			&errMsg
		);
	if (ret!=SQLITE_OK){
		LOG("%s\n",errMsg);
	}else{
		if (nRow<1){
			printf("No such area.\n");
		}else{
			char *updateSql=(char*)malloc(1024);
			sprintf(updateSql,UPDATE_SWITHCED_AREA_SQL,dbResult[1]);
			ret=sqlite3_exec(
					conn,
					updateSql,
					NULL,
					NULL,
					&errMsg
				);
			if (ret!=SQLITE_OK){
				LOG("%s\n",errMsg);
			}else{
				printf("Current arear swithced to %s.\n",area);
			}
			free(updateSql);
		}
	}
	free(selectSql);
	closeDb();
	return 0;
}

int areaAdd(char *area){
	openDb();
	char *errMsg;
	char *insertSql=(char*)malloc(1024);
	sprintf(insertSql,INSERT_AREA_SQL,area);	
	int	ret=sqlite3_exec(
			conn,
			insertSql,
			NULL,
			NULL,
			&errMsg
		);
	if (ret!=SQLITE_OK){
		LOG("%s\n",errMsg);
	}else{
		printf("Area %s added.\n",area);
	}
	free(insertSql);
	closeDb();
	return 0;
}

int taskShow(){
	openDb();
	char *errMsg;
	char **dbResult;
	int nRow,nColumn;
	long currentAreaId;
	
	int ret=sqlite3_get_table(
			conn,
			QUERY_CURRENT_AREA_ID_SQL,
			&dbResult,
			&nRow,
			&nColumn,
			&errMsg
		);
	if (ret==SQLITE_OK){
		currentAreaId=atol(dbResult[1]);
		printf("Current area is %ld...\n",currentAreaId);
	}else{
		printf("Query current area failed...\n");
		closeDb();
		return -1;
	}

	char *selectSql=(char*)malloc(1024);
	sprintf(selectSql,QUERY_TASK_BY_STATE_SQL,TASK_STATE_ACTIVE,currentAreaId);

	ret=sqlite3_get_table(
			conn,
			selectSql,
			&dbResult,
			&nRow,
			&nColumn,
			&errMsg
		);
	if (ret==SQLITE_OK){
		printf("%d tasks to do in total:\n",nRow);
		for (int i=0;i<nRow;i++){
			int startPos=(i+1)*nColumn;
			printf("%s\t%s\n",dbResult[startPos],dbResult[startPos+1]);
		}
	}else{
		printf("Query tasks to do failed...\n");
		closeDb();
		return -1;
	}

	closeDb();
	return 0;
}

int taskShowId(long taskId){
	openDb();
	char *errMsg;
	char **dbResult;
	int nRow,nColumn;
	
	char *selectSql=(char*)malloc(1024);
	sprintf(selectSql,QUERY_TASK_BY_ID_SQL,taskId);

	int ret=sqlite3_get_table(
			conn,
			selectSql,
			&dbResult,
			&nRow,
			&nColumn,
			&errMsg
		);
	if (ret==SQLITE_OK){
		if (nRow<1){
			printf("No such task with the given id!");
		}else{
			printf("Id:%ld\n",taskId);
			printf("Title:%s\n",dbResult[nColumn]);
			printf("Content:%s\n",dbResult[nColumn+1]);
			char *stateCode=dbResult[nColumn+2];
			char *stateString=NULL;
			if (strcmp(stateCode,TASK_STATE_ACTIVE)==0){
				stateString=TASK_STATE_ACTIVE_STRING;
			}else if (strcmp(stateCode,TASK_STATE_DONE)){
				stateString=TASK_STATE_DONE_STRING;
			}else
				LOG("Unrecognized task state code:%s\n",stateCode);
			if (stateString!=NULL)
				printf("State:%s\n",stateString);
		}
	}else{
		printf("Query task failed...\n");
	}

	closeDb();
	return 0;
}

int taskAdd(char *title,char *desc){
	openDb();
	char *errMsg;
	char *insertSql=(char*)malloc(1024);

	char **dbResult;
	int nRow,nColumn;
	long currentAreaId;	

	int ret=sqlite3_get_table(
			conn,
			QUERY_CURRENT_AREA_ID_SQL,
			&dbResult,
			&nRow,
			&nColumn,
			&errMsg
		);

	if (ret==SQLITE_OK){
		currentAreaId=atol(dbResult[1]);
		printf("Current area is %ld...\n",currentAreaId);
	}else{
		printf("Query current area failed...\n");
		closeDb();
		return -1;
	}

	sprintf(insertSql,INSERT_TASK_SQL,title,desc,TASK_STATE_ACTIVE,currentAreaId);	
	ret=sqlite3_exec(
			conn,
			insertSql,
			NULL,
			NULL,
			&errMsg
		);
	if (ret!=SQLITE_OK){
		LOG("%s\n",errMsg);
	}else{
		printf("Task %s added and its initial state is ACTIVE.\n",title);
	}
	free(insertSql);
	closeDb();

	return 0;
}

int taskDone(long taskId){
	openDb();
	char *errMsg;
	char *updateSql=(char*)malloc(1024);
	sprintf(updateSql,UPDATE_TASK_STATE_SQL,TASK_STATE_DONE,taskId);
	int ret=sqlite3_exec(
			conn,
			updateSql,
			NULL,
			NULL,
			&errMsg
		);
	if (ret!=SQLITE_OK){
		LOG("%s\n",errMsg);
	}else{
		printf("Task %ld has been done.\n",taskId);
	}
	closeDb();
	free(updateSql);
	return 0;
}

int help(){
	return 0;
}

