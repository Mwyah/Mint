#include "Rule.h"

#include <stdlib.h>
#include <string.h>

#include "stringLib.h"


Error createRule(Rule** rule) {
	Error res = Success;

	*rule = (Rule*) malloc(sizeof(Rule));

	if (!(*rule)) res = AllocationError;
	else {
		(*rule)->leftLen = 0;
		(*rule)->lenDiff = 0;
		(*rule)->left = NULL;
		(*rule)->right = NULL;
		(*rule)->next = NULL;
	}

	return res;
}

Error fillRule(Rule* rule, char* left, char* right, int ruleType) {
	Error res = Success;

	rule->leftLen = strlen(left);
	int rightLen = strlen(right);

	rule->left = (char*) malloc(rule->leftLen + 1);
	rule->right = (char*) malloc(rightLen + 1);

	if (!(rule->left) || !(rule->right)) res = AllocationError;
	else {
		rule->lenDiff = rightLen - rule->leftLen;
		rule->ruleType = ruleType;

		strcpy(rule->left, left);
		strcpy(rule->right, right);

		fillStopTable(&(rule->leftTable), rule->left, rule->leftLen);
	}

	return res;
}

void freeRule(Rule* rule) {
	free(rule->left);
	free(rule->right);

	free(rule);
}