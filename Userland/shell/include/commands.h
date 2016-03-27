#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <define.h>

#define COMMAND_FUNCTION(name) int cmd_ ## name(args_t args)
#define COMMAND_HELP(name) int help_ ## name(args_t args)
#define SUBCOMMAND_FUNCTION(name) static int scmd_ ## name(args_t args)

#define COMMAND(name) {#name, cmd_ ## name, help_ ## name}
#define SUBCOMMAND(name) {#name, scmd_ ## name, help_ ## name}

#define COMMAND_DECLARE(name) extern COMMAND_FUNCTION(name); extern COMMAND_HELP(name)
#define COMMAND_RUN(name, args) cmd_ ## name(args)
#define SUBCOMMAND_RUN(name, args) scmd_ ## name(args)

#define ARGS_FOR_SUBCOMMAND(args) if(args.argc != 0) { args.argc--; args.argv++; }

typedef struct {
	char * name;
	int (*run)(args_t args);
	int (*help)(args_t args);
} command_t;

#define _COMMANDS_SIZE 3
extern command_t commands[_COMMANDS_SIZE];

COMMAND_DECLARE(help);
COMMAND_DECLARE(echo);
COMMAND_DECLARE(time);

#endif
