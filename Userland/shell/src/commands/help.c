#include <commands.h>
#include <stdio.h>

COMMAND_HELP(help) = "<HELP> MESSAGE!";

COMMAND_FUNCTION(help) {
	int i;

	printf("<HELP> Args:");

	for(i = 0; i < args.argc; i++) {
		printf(" %s", args.argv[i]);
	}
	printf("\n");

	return OK;
}
