#include <commands.h>

command_t commands[_COMMANDS_SIZE] = {
	COMMAND(help),
	COMMAND(echo),
	COMMAND(time),
	// FUTURE COMMAND HERE !! REMEMBER TO CHANGE _COMMANDS_SIZE !!
}; // TODO: NULL terminated?
