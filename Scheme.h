#ifndef _MINT_SCHEME_H_
#define _MINT_SCHEME_H_

#include "Rule.h"

#include "errorHandle.h"


typedef struct Scheme {
	size_t num;
	Rule* rules;
} Scheme;


Error initScheme(Scheme* sch);

Error parseSchemeStr(Scheme* sch, char* str, size_t len);

Error addRule(Scheme* scheme, char* left, char* right, int ruleType);

void clearScheme(Scheme sch);

#endif