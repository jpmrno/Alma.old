#ifndef _HELP_H_
#define _HELP_H_

#define CMD_HELP_MSG "\
	Shows all available commands.\n\
	Usage: \"help\" or \"help <command>\".\n"

#define CMD_USER_MSG "\
	Changes the user name.\n\
	Usage: \"user <name>\".\n"

#define CMD_CLEAR_MSG "\
	Clears the screen.\n\
	Usage: \"clear\".\n"

#define CMD_TERMINAL_MSG "\
	Changes terminal or terminal configurations.\n\
	Usage: \"terminal <option>\",\n\
		where <option> field could be:\n\
			- \"set <number>\": changes the current terminal\n\
				to the one indicated by \"<number>\"\n\
				(possible values for \"<number>\": 1 or 2)\n\
			- \"background <value>\" or \"bg <value>\":\n\
				changes the current terminal background color\n\
			- \"text <value>\": changes the current terminal text color\n\
			- \"clear\": clears the content of the current terminal\n\
			Note: \"<value>\" is a number from 0 to 15 representing a color.\n"

#define CMD_TEXT_MSG "\
	Changes terminal text color.\n\
	Usage: \"color <value>\".\n\
		Note: \"<value>\" is a number from 0 to 15 representing a color.\n"

#define CMD_BACKGROUND_MSG "\
	Changes terminal background color.\n\
	Usage: \"background <value>\".\n\
		Note: \"<value>\" is a number from 0 to 15 representing a color.\n"

#define CMD_BG_MSG "\
	Changes terminal background color.\n\
	Usage: \"bg <value>\".\n\
		Note: \"<value>\" is a number from 0 to 15 representing a color.\n"

#define CMD_SCREENSAVER_MSG "\
	Sets Screen Saver options.\n\
	Usage: \"screensaver <option>\",\n\
		where <option> field could be:\n\
			- \"enable\": enables the screensaver activation\n\
			- \"disable\": disables the screensaver activation\n\
			- \"time <value>\": sets the time for the screensaver to appear\n\
				\"<value>\" field is a number from 5 to 999, representing\n\
					the time in seconds.\n" 

#define CMD_SS_MSG "\
	Sets Screen Saver options.\n\
	Usage: \"ss <option>\",\n\
		where <option> field could be:\n\
			- \"enable\": enables the screensaver activation\n\
			- \"disable\": disables the screensaver activation\n\
			- \"time <value>\": sets the time for the screensaver to appear\n\
				\"<value>\" field is a number from 5 to 999, representing\n\
					the time in seconds.\n" 	

#define CMD_TIME_MSG "\
	Sets Time options.\n\
	Usage:\n\
		- \"time\" or \"time get\": gets the system date and time\n\
		   with the format \"<day> <month> <year> <hour> <minute> <second>\"\n\
		- \"time set <day> <month> <year> <hour> <minute> <second>\":\n\
		   sets the system date and time based on the given values.\n"

#endif