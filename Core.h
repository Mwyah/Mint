#ifndef _MINT_CORE_H_
#define _MINT_CORE_H_

#include <stdlib.h>

#include "errorHandle.h"

#include "Scheme.h"
#include "Sequence.h"


typedef enum InputFlag {
	StandartInput,
	HelpInput,
	VersionInput
} InputFlag;


typedef struct Core {
	Scheme scheme;
	Sequence seq;
} Core;


Error initCore(Core* core);

Error parseInput(Core* core, InputFlag* inputFlag, int argc, char* argv[]);

Error runCore(Core* core);

void clearCore(Core core);


#endif