#include <commands.h>
#include <time.h>
#include <screen.h>
#include <help.h>

#define BACKGROUND 0
#define TEXT 1

// Remember to change CMDS_SIZE if a command is added
tCommand commands[CMDS_SIZE] = {
	{"help", cmd_help, CMD_HELP_MSG},
	// For future implementation
	//{"exit", cmd_exit, "Exits shell program.\n\tUsage: \"exit\".\n"},
	{"user", cmd_user, CMD_USER_MSG},
	{"clear", cmd_clear, CMD_CLEAR_MSG},
	{"terminal", cmd_terminal, CMD_TERMINAL_MSG},
	{"text", cmd_text, CMD_TEXT_MSG},
	{"background", cmd_background, CMD_BACKGROUND_MSG},
	{"bg", cmd_background, CMD_BG_MSG},
	{"screensaver", cmd_screensaver, CMD_SCREENSAVER_MSG},
	{"ss", cmd_screensaver, CMD_SS_MSG},
	{"time", cmd_time, CMD_TIME_MSG}
};

// Shell variables
extern char buffer[MAX_BUFFER_LENGTH];
extern char user[MAX_USER_NAME];
extern char * program;
extern int hasMoreArgs;
extern int completelyReadWord;

// Subcommands
static int scmd_help_command();
static int scmd_time_get();
static int scmd_time_set();
static int scmd_screensaver_enable();
static int scmd_screensaver_disable();
static int scmd_screensaver_time();
static int scmd_terminal_clear();
static int scmd_terminal_set();
static int scmd_terminal_color(int textBoolean);

/**
 * Prints the help message of desired command
 * @return OK if commands exists, !OK otherwise
 */
static int scmd_help_command() {
	int i; 

	// Search for the command in the list of commands
	for(i = 0; i < CMDS_SIZE; i++) {
		if(!strcmp(buffer, commands[i].name)) {
			printf("%s", commands[i].help);
			return OK;
		}
	}

	printf("\t<help> Command not found.\n");

	return ERROR;
}

/**
 * Reads the date and time from the System Time
 * @return   	OK if process could be completed
 *              !OK otherwise
 */
static int scmd_time_get() {
	int ret;
	systemTime_t t;

	if (hasMoreArgs) {
		return ERROR_ARGUMENTS_EXCESS;
	}

	ret = getSystemTime(&t); 
	printf("%d-%d-%d\t%d:%d:%d\n", 	t.day, t.month, t.year, t.hour, 
													t.minute, t.second);
	return ret;
}

/**
 * Writes the data received from arguments and transformed into a time type
 * to the System Time
 * @return   	OK if process could be completed
 *              !OK otherwise
 */
static int scmd_time_set() {
	systemTime_t t;
	char arg[MAX_TIME_NUM_LENGTH];
	int ret = 0;
	unsigned int convertedNum;
	int args[TIME_T_FIELDS] = {0};

	char *missings[] = {"day", "month", "year", "hour", 
													"minute", "second"};
	int i; 
	for (i = 0 ; i < TIME_T_FIELDS ; i++) {
		if (!hasMoreArgs) {
			printf("\t<time> Missing %s.\n", missings[i]);
			return ERROR_ARGUMENTS_MISSING;
		}
		getWord(arg, MAX_TIME_NUM_LENGTH);

		if (arg[0] == 0) {
			return ERROR_ARGUMENTS_MISSING;
		}

		ret = stringToNum(arg, &convertedNum);
		if (ret == ERROR_NUMBER_NOT_POSITIVE) {
		   printf("\t<time> Wrong argument: %s: Not a positive number.\n",arg);
		   return ERROR_ARGUMENTS_INVALID;
		}
		args[i] = convertedNum;
	}

	if(hasMoreArgs) {
		return ERROR_ARGUMENTS_EXCESS;
	}

	t.day = args[0];
	t.month = args[1];
	t.year = args[2];
	t.hour = args[3];
	t.minute = args[4];
	t.second = args[5];

	ret = setSystemTime(&t);
	if (ret == TIME_INVALID) {
		printf("\t<time> Wrong arguments: Not a valid Time.\n"
			"\t(note: year should be between 1980 & 2250).\n");
		return ERROR_ARGUMENTS_INVALID;
	}

	return OK;
}

/**
 * Enables the screen saver
 * @return         OK if process could be completed
 *                 !OK otherwise
 */
static int scmd_screensaver_enable() {
	if(hasMoreArgs) {
		return ERROR_ARGUMENTS_EXCESS;
	}

	enableScreenSaver();
	return OK;
}

/**
 * Disables the screen saver
 * @return         OK if process could be completed
 *                 !OK otherwise
 */
static int scmd_screensaver_disable() {
	if(hasMoreArgs) {
		return ERROR_ARGUMENTS_EXCESS;
	}

	disableScreenSaver();
	return OK;
}

/**
 * Sets the screensaver activation time
 * @return 		OK if process could be completed
 *              !OK otherwise
 */
static int scmd_screensaver_time() {
	char arg[MAX_SCREEN_SAVER_TIME_LENGTH];
	unsigned int seconds = 0;
	int ret = 0;

	if(!hasMoreArgs) {
		printf("\t<screensaver time>: Missing time.\n");
		return ERROR_ARGUMENTS_MISSING;
	}

	getWord(arg, MAX_SCREEN_SAVER_TIME_LENGTH);

	if (!completelyReadWord) {
		// The last space is for the '\0'
		printf("\t<screensaver time>:Time too long "
			"(max. length = %d digits).\n", MAX_SCREEN_SAVER_TIME_LENGTH - 1);
		return ERROR_ARGUMENTS_INVALID;
	}

	if(hasMoreArgs) {		
		return ERROR_ARGUMENTS_EXCESS;
	}

	if (arg[0] == 0) {
		return ERROR_ARGUMENTS_MISSING;
	}

	ret = stringToNum(arg, &seconds);
	if (ret == ERROR_NUMBER_NOT_POSITIVE) {
		printf("\t<screensaver time>: Wrong argument: %s: "
			"Not a positive number.\n", arg);
		return ERROR_ARGUMENTS_INVALID;
	}

	if(setScreenSaverTime(seconds) == ERROR_SCREENSAVER_TIME) {
		printf("\t<screensaver time>: Time invalid "
			"(min. time = %d seconds).\n", MIN_SCREENSAVER_TIME);
		return ERROR_ARGUMENTS_INVALID;
	}

	return OK;
}

/**
 * Clears the terminal screen
 * @return   OK if could clean, !OK otherwise
 */
static int scmd_terminal_clear() {
	if(hasMoreArgs) {
		return ERROR_ARGUMENTS_EXCESS;
	}

	clearScreen();
	return OK;
}

/**
 * Changes the current terminal to the one written in arguments
 * @return       OK if arguments are ok or error code otherwise
 */
static int scmd_terminal_set() {
	unsigned int index;
	int ret;
	char arg[MAX_TERMINAL_NUM_LENGTH];

	if(!hasMoreArgs) {
		printf("\t<terminal> Missing number.\n");
		return ERROR_ARGUMENTS_EXCESS;
	}

	getWord(arg, MAX_TERMINAL_NUM_LENGTH);

	if(!completelyReadWord) {
		printf("\t<terminal> Number too long (min. terminal = %d - "
			"max. terminal = %d).\n", MIN_TERMINAL, MAX_TERMINAL);
		return ERROR_ARGUMENTS_INVALID;
	}

	if(hasMoreArgs) {		
		return ERROR_ARGUMENTS_EXCESS;
	}

	if (arg[0] == 0) {
		return ERROR_ARGUMENTS_MISSING;
	}

	ret = stringToNum(arg, &index);
	if (ret == ERROR_NUMBER_NOT_POSITIVE) {
		printf("\t<terminal> Wrong argument: %s: Not a positive number.\n", 
																		arg);
		return ERROR_ARGUMENTS_INVALID;
	}

	ret = setTerminal(index);
	if(ret == ERROR_INVALID_TERMINAL) {
		printf("\t<terminal> Invalid terminal (min. terminal = %d - "
			"max. terminal = %d).\n", MIN_TERMINAL, MAX_TERMINAL);
		return ERROR_ARGUMENTS_INVALID;
	}

	return ret;
}

/**
 * Changes the terminal text color if argument "text" written 
 * Changes the terminal background color if argument "background" written 
 * @return       OK if the operation finished ok, error code otherwise
 */
static int scmd_terminal_color(int textBoolean) {
	unsigned int color;
	int ret = 0;
	char arg[MAX_COLOR_LENGTH];

	if(!hasMoreArgs) {
		printf("\t<terminal> Missing color.\n");
		return ERROR_ARGUMENTS_EXCESS;
	}

	getWord(arg, MAX_COLOR_LENGTH);

	if(!completelyReadWord) {
		printf("\t<terminal> Number too long (min. color = %d - "
			"max. color = %d).\n", MIN_COLOR, MAX_COLOR);
		return ERROR_ARGUMENTS_INVALID;
	}

	if(hasMoreArgs) {		
		return ERROR_ARGUMENTS_EXCESS;
	}

	if (arg[0] == 0) {
		return ERROR_ARGUMENTS_MISSING;
	}

	ret = stringToNum(arg, &color);
	if (ret == ERROR_NUMBER_NOT_POSITIVE) {
		printf("\t<terminal> Wrong argument: %s: Not a positive number.\n",
																		 arg);
		return ERROR_ARGUMENTS_INVALID;
	}

	if(textBoolean) {
		ret = setTerminalTextColor(color);
	} else {
		ret = setTerminalBackgroundColor(color);
	}

	if(ret == ERROR_INVALID_COLOR) {
		printf("\t<terminal> Number too long (min. color = %d - "
			"max. color = %d).\n", MIN_COLOR, MAX_COLOR);
		return ERROR_ARGUMENTS_INVALID;
	}

	return ret;
}

int cmd_user() {
	char newUser[MAX_USER_NAME];

	if(!hasMoreArgs) {
		printf("\t<user> Missing username.\n");
		return ERROR_ARGUMENTS_MISSING;
	}

	getWord(newUser, MAX_USER_NAME);

	if (!completelyReadWord) {
		// The last space is for the '\0' character
		printf("\t<user> Username too long (max. length = %d characters).\n", 
															MAX_USER_NAME - 1);
		return ERROR_ARGUMENTS_INVALID;
	}

	if(hasMoreArgs) {		
		return ERROR_ARGUMENTS_EXCESS;
	}

	strcpy(user, newUser);

	return OK;
}

int cmd_help() {
	int i;
	char * helpMsg = 0;

	if(!hasMoreArgs) {
		printf("\t%s\n", "<help> Available commands:");
		// Lists available commands
		for(i = 1; i < CMDS_SIZE; i++) {
			helpMsg = commands[i].name;
			if (helpMsg != 0)  {
				printf("\t\t-\t%s\n", helpMsg);
			}
		}
		printf("\n\t%s\n", "To show the help and usage of a command use: "
			"\"help <command>\".");

		return OK;
	}

	// Gets sub-command
	getWord(buffer, MAX_BUFFER_LENGTH);

	if(hasMoreArgs) {
		return ERROR_ARGUMENTS_EXCESS;
	}

	return scmd_help_command();	
}

int cmd_time() {
	if(!hasMoreArgs) {
		return scmd_time_get();
	}

	// Gets sub-command
	getWord(buffer, MAX_BUFFER_LENGTH);

	if(!strcmp(buffer, "get")) {
		return scmd_time_get();
	}

	if(!strcmp(buffer, "set")) {
		return scmd_time_set();
	}

	printf("\t<time> Invalid option.\n");

	return ERROR_ARGUMENTS_INVALID;
}

int cmd_screensaver() {
	if(!hasMoreArgs) {
		return ERROR_ARGUMENTS_MISSING;
	}

	// Gets sub-command
	getWord(buffer, MAX_BUFFER_LENGTH);

	if(!strcmp(buffer, "enable")) {
		return scmd_screensaver_enable();
	}

	if(!strcmp(buffer, "disable")) {
		return scmd_screensaver_disable();
	}

	if(!strcmp(buffer, "time")) {
		return scmd_screensaver_time();
	}

	// if(!strcmp(buffer, "set")) {
	// 	return scmd_screensaver_set();
	// }

	printf("\t<screensaver> Invalid option.\n");

	return ERROR_ARGUMENTS_INVALID;
}

int cmd_terminal() {
	if(!hasMoreArgs) {
		return ERROR_ARGUMENTS_MISSING;
	}

	// Gets sub-command
	getWord(buffer, MAX_BUFFER_LENGTH);

	if(!strcmp(buffer, "clear")) {
		return scmd_terminal_clear();
	}

	if(!strcmp(buffer, "set")) {
		return scmd_terminal_set();
	}

	if(!strcmp(buffer, "text")) {
		return scmd_terminal_color(TEXT);
	}

	if((!strcmp(buffer, "background")) || (!strcmp(buffer, "bg"))) {
		return scmd_terminal_color(BACKGROUND);
	}

	printf("\t<terminal> Invalid option.\n");

	return ERROR_ARGUMENTS_INVALID;
}

int cmd_clear() {
	return scmd_terminal_clear();
}

int cmd_text() {
	if(!hasMoreArgs) {
		printf("<terminal> Missing color\n");
		return ERROR_ARGUMENTS_MISSING;
	}

	return scmd_terminal_color(TEXT);
}

int cmd_background() {
	if(!hasMoreArgs) {
		printf("<terminal> Missing color\n");
		return ERROR_ARGUMENTS_MISSING;
	}

	return scmd_terminal_color(BACKGROUND);
}
