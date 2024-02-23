#ifndef INTERRUPTS
#define INTERRUPTS
#include "../../headers/const.h"
#include "../../headers/types.h"
#include "initial.h" //not defined yet
#include <umps/const.h>
#include <umps/libumps.h>
#include <umps/arch.h>

void interruptsHandler(int cause);

#endif
