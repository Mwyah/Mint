#include "errorHandle.h"

#include <stdlib.h>
#include <stdio.h>

#include "settings.h"


void callError(Error error) {
	switch (error) {
	case Success:
		break;

	case AllocationError:
		printf("Allocation error: interpreter couldn't allocate memory for its needs. Maybe try again :)\n");
		break;

	case InputSeqOutOfRangeError:
		printf("Input sequence is too large. Its length cannot exceed %zi (include '\\0' character)\n", MAX_SEQ_MEM);
		break;

	case InputExtraSeqError:
		printf("Input contains multiple sequences, but it should contains only one\n");
		break;

	case InputUnknownCommandError:
		printf("Input contains unknown commands. Use --help to see the list of commands\n");
		break;

	case InputWrongScheme:
		printf("Input rules have incorrect syntax\n");
		break;

	case RuntimeSeqOutOfRange:
		printf("Sequence became larger than limit (%s) during the runtime.\n", MAX_SEQ_MEM);
		break;

	default:
		printf("Unknown error. 00110011011011!!!!001!01\n");
		break;
	}
}