#include "Core.h"

#include <stdio.h>
#include <string.h>

#include "settings.h"
#include "stringLib.h"


typedef struct Tag {
	char* tag;
	unsigned len;
} Tag;


static int findTag(char** arg, Tag tag) {

	int res = 1;

	if (strlen(*arg) < tag.len) res = 0;
	else {
		for (int i=0; i<tag.len; i++) {
			if ((*arg)[i] != tag.tag[i]) {
				res = 0;
				break;
			}
		}
	}

	if (res) {
		*arg += tag.len;
	}

	return res;
}


Error initCore(Core* core) {

	Error res = Success;

	res = initScheme(&(core->scheme));
	if (!res) res = initSequence(&(core->seq));

	return res;
}

Error parseInput(Core* core, InputFlag* inputFlag, int argc, char* argv[]) {  // Need to add file reading

	Error res = Success;
	*inputFlag = StandartInput;
	int seqFlag = 0;

	size_t inputTagsNum = 6;
	Tag inputTags[] = {{"-r", 2}, {"-R", 2},
						{"-s", 2}, {"-S", 2},
						{"--help", 6}, {"--version", 9}};


	if (argc == 0) *inputFlag = HelpInput;

	for (int i=0; i<argc; i++) {
		char* arg = argv[i];

		int tagFlag = -1;
		for (int j=0; j<inputTagsNum; j++) {
			if (findTag(&arg, inputTags[j])) {
				tagFlag = j;
				break;
			}
		}

		switch (tagFlag) {
		case 0:               // -r
			res = parseSchemeStr(&(core->scheme), arg, strlen(arg));
			break;

		case 1:               // -R
			break;

		case 2:               // -s
			if (seqFlag) {
				res = InputExtraSeqError;
			}
			else {
				seqFlag = 1;

				res = fillSequence(&(core->seq), arg, strlen(arg));
			}

			break;

		case 3:               // -S
			break;

		case 4:               // --help
			*inputFlag = HelpInput;
			break;

		case 5:               // --version
			*inputFlag = VersionInput;
			break;

		case -1:              // unknown
			res = InputUnknownCommandError;
			break;
		}

		if ((*inputFlag != StandartInput) && (res)) break;
	}

	return res;
}

Error runCore(Core* core) {
	Error res = Success;

	int isFinal = 0;
	while(!isFinal) {
		isFinal = 1;

		Rule* rl = core->scheme.rules;
		int ind = -1;
		while (rl) {
			ind = findSubstr(&(core->seq), rl);

			if (ind == -1) rl = rl->next;
			else {
				res = replaceSubstr(&(core->seq), rl, ind);

				if (rl->ruleType == 0) isFinal = 0;

				break;
			}
		}

		if (res) break;
	}

	return res;
}

void clearCore(Core core) {
	clearScheme(core.scheme);
	clearSeq(core.seq);
}