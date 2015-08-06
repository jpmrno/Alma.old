#include <timertick.h>

/**
 * [Copied from its definition at: manager.c]
 * Receives a signal from the timerTickHandler function (see: timertick.c)
 * each time that function is called.
 *
 * IMPORTANT: This function should be only used by the timerTickHandler
 * function at: timertick.c. That's why its declaration is not included 
 * at: manager.h
 */
void manager_timerTickInterrupt();

void timerTickHandler() {

	manager_timerTickInterrupt();
	return;
}
