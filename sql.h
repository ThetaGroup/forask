#define CREATE_AREA_TABLE_SQL "create table area(id integer primary key autoincrement,name varchar(128));"
#define CREATE_TASK_TABLE_SQL "create table task(id integer primary key autoincrement,title varchar(128),content varchar(1024),state varchar(2),areaId integer);"
#define CREATE_CONFIG_TABLE_SQL "create table config(id integer primary key autoincrement,name varchar(128),attr varchar(128));"

#define INSERT_CURRENT_AREA_CONFIG_SQL "insert into config (name,attr) values ('current_area',NULL);"
#define INSERT_AREA_SQL "insert into area (name) values ('%s');"
#define INSERT_TASK_SQL "insert into task (title,content,state,areaId) values ('%s','%s','%s','%ld');"

#define UPDATE_SWITHCED_AREA_SQL "update config set attr='%s' where name='current_area';"
#define UPDATE_TASK_STATE_SQL "update task set state='%s' where  id='%ld';"

#define QUERY_ALL_AREA_SQL "select name from area;"
#define QUERY_CURRENT_AREA_SQL "select area.name from config left join area on config.attr=area.id where config.name='current_area';"
#define QUERY_CURRENT_AREA_ID_SQL "select area.id from config left join area on config.attr=area.id where config.name='current_area';"
#define QUERY_CERTAIN_AREA_SQL "select id from area where name='%s';"
#define QUERY_TASK_BY_STATE_SQL "select id,title,content from task where state='%s' and areaId='%ld';"
#define QUERY_TASK_BY_ID_SQL "select title,content,state from task where id='%ld';"
