#include <commands.h>
#include <stdio.h>

COMMAND_FUNCTION(echo) {
	int i;

	if(!args.argc) {
		printf("<echo> Error: no arguments.\n");

		return ERROR;
	}

	for(i = 0; i < args.argc; i++) {
		printf("%s ", args.argv[i]);
	}
	printf("\b\n");

	return OK;
}

COMMAND_HELP(echo) {
	if(args.argc >= 1) {
		printf("<echo> Error: too many arguments.\n");

		return ERROR;
	}

	printf("<echo> Write arguments to the standard output.\n");
	printf("<echo> Usage: 'echo [string ...]'\n");

	return OK;
}
