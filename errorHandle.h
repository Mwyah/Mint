#ifndef _MINT_ERRORHANDLE_H_
#define _MINT_ERRORHANDLE_H_


typedef enum Error {
	Success,                     // No errors
	AllocationError,             // Error of memory allocation
	InputSeqOutOfRangeError,     // Input sequence (-s or -S) is larger than MAX_SEQ_MEM
	InputExtraSeqError,          // Input have several sequences. Input must have only one sequence
	InputUnknownCommandError,    // Input have unknown command (existing commands: -s -S -r -R --help --version)
	InputWrongScheme,            // Input rules (-r or -R) have wrong syntax
	RuntimeSeqOutOfRange         // Sequence became larger than MAX_SEQ_MEM during the runtime
} Error;


void callError(Error error);


#endif