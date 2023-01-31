#include "Sequence.h"

#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "errorHandle.h"


Error initSequence(Sequence* seq) {
	Error res = Success;

	if (!seq) res = AllocationError;
	else {
		seq->len = 0;
		seq->mem = 0;
		seq->mainStr = NULL;
		seq->suppStr = NULL;
	}

	return res;
}

Error fillSequence(Sequence* seq, char* str, size_t len) {
	Error res = Success;

	len++;

	if (len > MAX_SEQ_MEM) res = InputSeqOutOfRangeError;
	else {
		seq->mainStr = (char*) malloc(min(len*2, MAX_SEQ_MEM));
		seq->suppStr = (char*) malloc(min(len*2, MAX_SEQ_MEM));

		if (!(seq->mainStr) || !(seq->suppStr)) res = AllocationError;
		else {
			strcpy(seq->mainStr, str);
			seq->len = len-1;
			seq->mem = min(len*2, MAX_SEQ_MEM);
		}
	}

	return res;
}

void swap(Sequence* seq) {
	char* tmp = seq->mainStr;
	seq->mainStr = seq->suppStr;
	seq->suppStr = tmp;
}

void clearSeq(Sequence seq) {
	free(seq.mainStr);
	free(seq.suppStr);

	seq.mainStr = NULL;
	seq.suppStr = NULL;
	seq.len = 0;
	seq.mem = 0;
}