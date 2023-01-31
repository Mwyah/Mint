#include "stringLib.h"

#include <stdlib.h>
#include <string.h>

#include "settings.h"


void fillStopTable(int* table, char* str, int len) {

	for (int i=0; i<256; i++) table[i] = -1;

	for (int i=0; i<len; i++) {
		table[(unsigned char) str[i]] = i;

		str++;
	}
}

int findSubstr(Sequence* seq, Rule* rule) {
	if (seq->len >= rule->leftLen) {
		if (rule->leftLen == 0) return -1;

		for (int i=0; i <= (seq->len - rule->leftLen); ) {

			int j;
			for (j = rule->leftLen - 1; (rule->left)[j] == (seq->mainStr)[i+j]; j--) {
				if (j == 0) return (i);
			}

			i += j - (rule->leftTable)[(unsigned char) (seq->mainStr)[i+j]];
		}
	}

	return -1;
}

Error replaceSubstr(Sequence* seq, Rule* rule, int pos) {
	Error res = Success;

	seq->len += rule->lenDiff;

	if (seq->len + 1 > MAX_SEQ_MEM) res = RuntimeSeqOutOfRange;
	else {
		int memFlag = 0;

		if (seq->len + 1 > seq->mem) {
			memFlag = 1;

			free(seq->suppStr);

			seq->mem = min(max(seq->mem*2, seq->len+1), MAX_SEQ_MEM); 
			seq->suppStr = (char*) malloc(seq->mem);
		}

		if (!(seq->suppStr)) res = AllocationError;
		else {

			strncpy(seq->suppStr, seq->mainStr, pos);
			strcpy(seq->suppStr + pos, rule->right);
			strcat(seq->suppStr, seq->mainStr + pos + rule->leftLen);

			swap(seq);

			if (memFlag) {
				free(seq->suppStr);

				seq->suppStr = (char*) malloc(seq->mem);

				if (!(seq->suppStr)) res = AllocationError;
			}
		}
	}

	return res;
}