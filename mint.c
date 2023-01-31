#include <stdio.h>
#include <string.h>

#include "Core.h"
#include "settings.h"


int main(int argc, char* argv[]) {

	Error res = Success;
	InputFlag inputFlag;
	Core core;
	

	res = initCore(&core);

	if (!res) {
		res = parseInput(&core, &inputFlag, argc-1, argv+1);

		if (!res) {
			
			if (inputFlag == 0) {
				res = runCore(&core);

				if (!res) printf("%s\n", core.seq.mainStr);
			}
			else if (inputFlag == 1) printf("%s\n", HELP_MESSAGE);
			else if (inputFlag == 2) printf("%s\n", VERSION_MESSAGE);
		}
	}


	callError(res);

	clearCore(core);

	return res;
}