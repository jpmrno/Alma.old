#include <shell.h>
#include <stdio.h>
#include <commands.h>
#include <memory.h>

// Module setup
extern char bss;
extern char endOfBinary;

char buffer[MAX_BUFFER_LENGTH];
char user[MAX_USER_NAME] = "root";
char * program = "shell";
int hasMoreArgs = FALSE;
int completelyReadWord = FALSE;
extern tCommand commands[CMDS_SIZE];

static void clearBuffer();
static int runCmd(const char * cmd);

int main() {
	//Clean BSS
	memset(&bss, 0, &endOfBinary - &bss);

	int ret;

	// Shell cycle
	while(TRUE) {
		// Print prompt
		printf("%s@%s:$> ", user, program);

		// Gets the command string to run
		getWord(buffer, MAX_BUFFER_LENGTH);

		// Interprets command and runs it
		ret = runCmd(buffer);

		// If command returned error, print it
		if(ret != OK) {
			// Clears buffer so not to read something from previous invalid
			// or wrong command
			clearBuffer();
			printError(ret);
		} else {
			// Necessary for future exit implementation.
		}
 	}

	return OK;
}

/**
 * Interprets and runs the command
 * @param  cmd  the string of the command to run
 * @return     OK if command runned ok, error code otherwise
 */
static int runCmd(const char * cmd) {
	int i = 0;

	if(cmd[0] == 0) {
		return ERROR_CMD_EMPTY;
	}

	// Search for the command in the list of commands
	for(i = 0; i < CMDS_SIZE; i++) {
		if(!strcmp(cmd, commands[i].name)) {
			return commands[i].func();
		}
	}

	return ERROR_CMD_INVALID;
}

/**
 * Advances the buffer to a '\n'
 */
static void clearBuffer() {
	if(hasMoreArgs) {
		uint8_t c;
		while((c = getchar()) != '\n');
		hasMoreArgs = FALSE;
	}
}

int getWord(char * cmd, int max) {
	int cmdLength = scanw(cmd, max);

	hasMoreArgs = (cmd[cmdLength] != '\n') ? TRUE : FALSE;
	completelyReadWord = (!hasMoreArgs || cmd[cmdLength] == ' ') ? TRUE:FALSE;

	cmd[cmdLength] = 0;

	return cmdLength;
}

void printError(int error) {
	char * msj;

	switch(error) {
		case ERROR_CMD_INVALID:
			msj = "Invalid command.\n\tUse help command to show a list of "
														"possible commands";
			break;
		case ERROR_ARGUMENTS_MISSING:
			msj = "Missing arguments";
			break;
		case ERROR_ARGUMENTS_EXCESS:
			msj = "Too many arguments (check not to have final spaces)";
			break;
		case ERROR_ARGUMENTS_INVALID:
			msj = "Invalid arguments";
			break;
		default:
			return;
	}

	printf("\t<ERROR> %s.\n", msj);
}
