#ifndef _PIT_H_
#define _PIT_H_

void pit_init();
void pit_set(unsigned int miliseconds);
void pit_wait(unsigned int seconds);

#endif
