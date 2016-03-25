#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <define.h>

#define COMMAND_FUNCTION(name) int cmd_ ## name(args_t args)
#define SUBCOMMAND_FUNCTION(name, option) int cmd_ ## name ## _ ## option(args_t args)
#define COMMAND_HELP(name) SUBCOMMAND_FUNCTION(name, help)
#define COMMAND_DECLARE(name) extern COMMAND_FUNCTION(name); extern COMMAND_HELP(name)
#define COMMAND(name) {#name, cmd_ ## name, cmd_ ## name ## _help}
// #define COMMAND_RUN(name, args) cmd_ ## name(args) // TODO: remove

typedef struct {
	char * name;
	int (*run)(args_t args);
	int (*help)(args_t args);
} command_t;

#define _COMMANDS_SIZE 1
extern command_t commands[_COMMANDS_SIZE];

COMMAND_DECLARE(echo);

#endif
