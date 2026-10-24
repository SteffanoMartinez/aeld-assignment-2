#include <stdio.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

// man for syslog mentions that openlog and closelog API's are optional, but on bigger projects, its better to control the flow.

int main(int argc, char *argv[]){
	openlog("writer",0,LOG_USER);

	if (argc != 3){
		syslog(LOG_ERR,"Incorrect number of arguments passed, received %d, "
			       	"you must pass as the FIRST argument the filepath "
				"and as SECOND argument the string to write.",argc - 1);
		closelog();
		return 1;
	}
	
	// const due to never wanting to change these arguments.
	const char *filepath = argv[1];
	const char *text = argv[2];

	FILE *current_file = fopen(filepath,"w"); // truncate or overwrite a file, creates one if it does not exist, just like writer.sh
	if (current_file == NULL){
		int err = errno;
		syslog(LOG_ERR,"Unable to open filepath %s: %s",filepath,strerror(err));
		closelog();
		return 1;
	}		

	
	syslog(LOG_DEBUG,"Writing %s to %s", text, filepath);
	int write_action = fputs(text, current_file);
       	if (write_action == EOF){
		int err = errno;
		syslog(LOG_ERR,"Error at writing %s at filepath %s : %s",text,filepath,strerror(err));
		fclose(current_file); // In-line close, since this error is secondary, so not overwritting errno. 
		closelog();
		return 1;
	} 

	int close_action = fclose(current_file);
	if (close_action != 0){
		int err = errno;
		syslog(LOG_ERR,"Error at closing %s : %s",filepath,strerror(err));
		closelog();
		return 1;
	}

	closelog();
	return 0;
}

