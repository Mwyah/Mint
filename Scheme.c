#include "Scheme.h"

#include <stdlib.h>


static Error addChar(char** str, int* mem, int* len, char ch) {
	Error res = Success;

	if (len == mem) {
		(*mem) *= 2;
		char* tmp = (char*) realloc(*str, *mem);
		if (!tmp) res = AllocationError;
		else *str = tmp;
	}

	(*str)[*len] = ch;
	(*len)++;

	return res;
}

Error initScheme(Scheme* sch) {

	Error res = Success;

	if (!sch) res = AllocationError;
	else {
		sch->num = 0;
		sch->rules = NULL;
	}

	return res;
}

Error parseSchemeStr(Scheme* sch, char* str, size_t len) {
	Error res = Success;

	int parseMemLeft    = 32;
	int parseMemRight   = 32;
	char* parseResLeft  = (char*) malloc(parseMemLeft);
	char* parseResRight = (char*) malloc(parseMemRight);

	if (!parseResLeft || !parseResRight) res = AllocationError;
	else {
		int parseLenLeft   = 0;
		int parseLenRight  = 0;

		int breakFlag      = 0;
		int ruleFlag       = 0;
		int arrowFlag      = 0;
		int spaceFlag      = 0;
		int escapeCharFlag = 0;
		int bracketCount   = 0;

		while (!breakFlag && !res) {

			switch (*str) {
			case '\\':
				if (ruleFlag == 0) res = InputWrongScheme;
				else {
					if (escapeCharFlag == 1) {
						escapeCharFlag = 0;
						res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '\\')
							: addChar(&parseResRight, &parseMemRight, &parseLenRight, '\\');
					}
					else escapeCharFlag = 1;
				}

				spaceFlag = 0;

				break;

			case '-':
				if (ruleFlag == 0) {
					if (arrowFlag != 0) res = InputWrongScheme;
					else arrowFlag = 1;
				}
				else {
					if (escapeCharFlag == 1) {
						escapeCharFlag = 0;
						res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '\\')
							: addChar(&parseResRight, &parseMemRight, &parseLenRight, '\\');
					}
					if (!res) {
						res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '-')
							: addChar(&parseResRight, &parseMemRight, &parseLenRight, '-');
					}
				}

				spaceFlag = 0;

				break;

			case '=':
				if (ruleFlag == 0) {
					if (arrowFlag != 0) res = InputWrongScheme;
					else arrowFlag = -1;
				}
				else {
					if (escapeCharFlag == 1) {
						escapeCharFlag = 0;
						res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '\\')
							: addChar(&parseResRight, &parseMemRight, &parseLenRight, '\\');
					}
					if (!res) {
						res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '=')
							: addChar(&parseResRight, &parseMemRight, &parseLenRight, '=');
					}
				}

				spaceFlag = 0;

				break;

			case '>':
				if (ruleFlag == 0) {
					if (arrowFlag ==  0) res = InputWrongScheme;
					if (arrowFlag ==  1) arrowFlag = 2;
					if (arrowFlag == -1) arrowFlag = -2;
				}

				spaceFlag = 0; 

				break;

			case '[':
				if (escapeCharFlag == 1) {
					escapeCharFlag = 0;
					res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '[')
						: addChar(&parseResRight, &parseMemRight, &parseLenRight, '[');
				}
				else {
					if (ruleFlag == 0) res = InputWrongScheme;
					else {
						if (bracketCount == 0) bracketCount = 1;
						else res = InputWrongScheme;
					}
				}

				spaceFlag = 0;

				break;

			case ']':
				if (escapeCharFlag == 1) {
					escapeCharFlag = 0;
					res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, ']')
						: addChar(&parseResRight, &parseMemRight, &parseLenRight, ']');
				}
				else {
					if (ruleFlag == 0) res = InputWrongScheme;
					else {
						if (bracketCount == 1) bracketCount = 0;
						else res = InputWrongScheme;
					}
				}

				spaceFlag = 0;

				break;

			case ' ':
				if (ruleFlag == 0) {
					if (arrowFlag == 2 || arrowFlag == -2) ruleFlag = 1;
					else if (arrowFlag != 0) res = InputWrongScheme;
				}
				else if (ruleFlag == 1) {
					if (escapeCharFlag == 1) {
						escapeCharFlag = 0;
						res = addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '\\');
					}

					if (bracketCount == 1) res = addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, ' ');
					else if (spaceFlag == 0) {
						ruleFlag = 2;
						res = addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '\0');
					}
				}
				else if (ruleFlag == 2) {
					if (escapeCharFlag == 1) {
						escapeCharFlag = 0;
						res = addChar(&parseResRight, &parseMemRight, &parseLenRight, '\\');
					}

					if (bracketCount == 1) res = addChar(&parseResRight, &parseMemRight, &parseLenRight, ' ');
					else if (spaceFlag == 0) {
						ruleFlag = 3;
						res = addChar(&parseResRight, &parseMemRight, &parseLenRight, '\0');
					}
				}

				spaceFlag = 1;

				break;

			case '\0':
				if (ruleFlag == 0 || ruleFlag == 1) res = InputWrongScheme;
				else if (bracketCount == 1) res = InputWrongScheme;
				else if (ruleFlag == 2) {
					if (escapeCharFlag == 1) res = InputWrongScheme;
					else {
						ruleFlag = 3;
						res = addChar(&parseResRight, &parseMemRight, &parseLenRight, '\0');
					}
				}

				breakFlag = 1;
				break;

			default:
				if (ruleFlag == 0) res = InputWrongScheme;
				else {
					if (escapeCharFlag == 1) {
						escapeCharFlag = 0;
						res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, '\\')
							: addChar(&parseResRight, &parseMemRight, &parseLenRight, '\\');
					}

					if (!res) {
						res = (ruleFlag == 1) ? addChar(&parseResLeft, &parseMemLeft, &parseLenLeft, *str)
							: addChar(&parseResRight, &parseMemRight, &parseLenRight, *str);
					}
				}

				spaceFlag = 0;

				break;
			}

			if (ruleFlag == 3) {
				res = addRule(sch, parseResLeft, parseResRight, (arrowFlag == 2) ? 0 : 1);
				arrowFlag     = 0;
				ruleFlag      = 0;
				parseLenLeft  = 0;
				parseLenRight = 0;
			}

			if (!breakFlag) str++;
		}
	}


	free(parseResLeft);
	free(parseResRight);

	return res;
}

Error addRule(Scheme* scheme, char* left, char* right, int ruleType) {
	Error res = Success;

	Rule* rl = scheme->rules;

	if (!rl) {
		res = createRule(&(scheme->rules));

		if (!res) res = fillRule(scheme->rules, left, right, ruleType);
	}
	else {
		while(rl->next) rl = rl->next;

		res = createRule(&(rl->next));

		if (!res) res = fillRule(rl->next, left, right, ruleType);
	}

	scheme->num++;

	return res;
}

void clearScheme(Scheme sch) {

	Rule* tmp = sch.rules;
	Rule* tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		freeRule(tmp);
		tmp = tmp2;
	}

	sch.rules = NULL;
	sch.num = 0;
}