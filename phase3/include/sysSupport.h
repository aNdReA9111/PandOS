#ifndef SYSSUPPORT

#include "../../headers/const.h"
#include "../../headers/types.h"
#include "../../headers/listx.h"
#include "../../phase1/headers/pcb.h"
#include "../../phase1/headers/msg.h"
#include "../../phase2/include/timers.h"
#include "../../phase2/include/exceptions.h"
#include <umps/const.h>
#include <umps/libumps.h>
#include <umps/arch.h>
#include <umps/cp0.h>

void generalExceptionHandler();
void syscallExceptionHandler(state_t *exception_state);
void programTrapExceptionHandler(state_t *exception_state);

#endif 