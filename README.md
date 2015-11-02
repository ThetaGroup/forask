<!-- 
	author:Ranger
	org:Theta Group
-->
# Forask
Theta Task -> 2Task -> 3Task -> 4Task -> Forask

----
## Command

* forask
	+ area
		* show : Show all areas.
		* switch %name : Switch current area by names.
		* add %name : Add a new area with its name.
	+ task 
		* show (%id) : Show certain/all task(s) with/without id.
		* add %name %content : Add a new task with its name and content.
		* done %id : Finish a task with its id.
	+ sync :To do...
	+ help :To do...

----
## Data

Export forask.db file using any sqlite client.Here we ignore the details of tables & datas within,check it yourself.

***For now,I hard code the db-file's location in /etc/forask.db(in Unix-Family).This should be fixed in later versions.***

