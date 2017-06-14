#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cli.h"
#include "command.h"
#include "log.h"

int analyseParameters(int argc,char *argv[]){
	if (argc==1){
		return CLI_HELP;
	}else{
		if (strcmp(argv[1],"area")==0){
			if (argc==2){
				return CLI_AREA_SHOW;
			}else if (argc==4 && strcmp(argv[2],"switch")==0){
				return CLI_AREA_SWITCH;
			}else if (argc==4 && strcmp(argv[2],"add")==0){
				return CLI_AREA_ADD;
			}
		}else if (strcmp(argv[1],"task")==0){
			if (argc==2 || (argc==3 && strcmp(argv[2],"show")==0)){
				return CLI_TASK_SHOW;
			}else if (argc==4 && strcmp(argv[2],"show")==0){
				return CLI_TASK_SHOW_ID;
			}else if (argc==4 && strcmp(argv[2],"done")==0){
				return CLI_TASK_DONE;
			}else if (argc==5 && strcmp(argv[2],"add")==0){
				return CLI_TASK_ADD;
			}
		}else if (argc==2 && strcmp(argv[1],"sync")==0){
			return CLI_SYNC;
		}
	}
	return CLI_ERROR;
}

int runClient(int argc,char *argv[]){
	int opt=analyseParameters(argc,argv);
	switch (opt){
		case CLI_SYNC:
			LOG("Sync...\n");
			return sync();
		case CLI_AREA_SHOW:
			LOG("Area Show...\n");
			return areaShow();
		case CLI_AREA_SWITCH:
			LOG("Area Switch...\n");
			return areaSwitch(argv[3]);
		case CLI_AREA_ADD:
			LOG("Area Add...\n");
			return areaAdd(argv[3]);
		case CLI_TASK_SHOW:
			LOG("Task Show...\n");
			return taskShow();
		case CLI_TASK_SHOW_ID:
			LOG("Task Show Id...\n");
			return taskShowId(atol(argv[3]));
		case CLI_TASK_ADD:
			LOG("Task Add...\n");
			return taskAdd(argv[3],argv[4]);
		case CLI_TASK_DONE:
			LOG("Task Done...\n");
			return taskDone(atol(argv[3]));
		case CLI_HELP:
			LOG("Help...\n");
			return help();
		case CLI_ERROR:
		default:
			printf("Unrecognized parameters!\n");
	}
	return 0;
}
