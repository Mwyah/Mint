#ifndef _MINT_SEQUENCE_H_
#define _MINT_SEQUENCE_H_

#include "errorHandle.h"


typedef struct Sequence {
	char* mainStr;
	char* suppStr;

	size_t len;
	size_t mem;
} Sequence;


Error initSequence(Sequence* seq);

Error fillSequence(Sequence* seq, char* str, size_t len);

void swap(Sequence* seq);

void clearSeq(Sequence seq);

#endif
