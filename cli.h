#define CLI_SYNC 00
#define CLI_AREA_SHOW 11
#define CLI_AREA_SWITCH 12
#define CLI_AREA_ADD 13
#define CLI_TASK_SHOW 21
#define CLI_TASK_SHOW_ID 22
#define CLI_TASK_ADD 23
#define CLI_TASK_DONE 24
#define CLI_HELP 98
#define CLI_ERROR 99

int analyseParameters(int argc,char *argv[]);

int runClient(int argc,char *argv[]);
