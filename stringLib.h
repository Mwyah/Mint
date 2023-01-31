#ifndef _MINT_STRINGLIB_H_
#define _MINT_STRINGLIB_H_

#include <stddef.h>

#include "Sequence.h"
#include "Rule.h"


void fillStopTable(int* table, char* str, int len);       // table[256]

int findSubstr(Sequence* seq, Rule* rule);

Error replaceSubstr(Sequence* seq, Rule* rule, int pos);


#endif