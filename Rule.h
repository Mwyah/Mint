#ifndef _MINT_RULE_H_
#define _MINT_RULE_H_

#include <stddef.h>

#include "errorHandle.h"


typedef struct Rule {
	int ruleType;     // 0 - simple rule, 1 - exit rule

	char* left;
	char* right;

	size_t leftLen;
	int lenDiff;      // rightLen - leftLen 

	int leftTable[256];

	struct Rule* next;
} Rule;


Error createRule(Rule** rule);

Error fillRule(Rule* rule, char* left, char* right, int ruleType);

void freeRule(Rule* rule);

#endif
