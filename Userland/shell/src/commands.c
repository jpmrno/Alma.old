#include <commands.h>

// 				USAGE
// 
// -- [ commands/name.c ] ------------
// (1) COMMAND_FUNCTION(name) { ... }
// (2) COMMAND_HELP(name) { ... }
// (*) SUBCOMMANDS
// -----------------------------------
// 
// -- [ commands.c ] -----------------
// (3) COMMAND(name),
// (4) COMMAND_DECLARE(name);
// -----------------------------------
// 
//			 ^^ USAGE ^^

COMMAND_DECLARE(help);
COMMAND_DECLARE(echo);
COMMAND_DECLARE(time);

command_t commands[] = {
	COMMAND(help),
	COMMAND(echo),
	COMMAND(time),
	// FUTURE COMMAND HERE !!
	{ NULL, NULL, NULL}
};
