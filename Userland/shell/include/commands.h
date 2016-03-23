#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <define.h>

#define COMMAND_FUNCTION(name) int cmd_ ## name(args_t args)
#define COMMAND_HELP(name) const char * cmd_ ## name ## _help
#define COMMAND_DECLARE(name) extern COMMAND_FUNCTION(name); extern COMMAND_HELP(name)
#define COMMAND(name) {#name, cmd_ ## name, "cmd_ ## name ## _help"}
#define COMMAND_RUN(name, args) cmd_ ## name(args)

typedef struct {
	char * name;
	int (*run)(args_t args);
	char * help;
} command_t;

#define _COMMANDS_SIZE 1
extern command_t commands[_COMMANDS_SIZE];

COMMAND_DECLARE(help);

#endif
