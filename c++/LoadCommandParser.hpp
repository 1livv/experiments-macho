#include <vector>
#include <stdio.h>
#include "LoadSegmentCommand.hpp"
#include "LoadDyLibCommand.hpp"
#include "FileUtils.hpp"


#define LC_SEGMENT 	0x1
#define LC_SEGMENT_64 	0x19
#define LC_LOAD_DYLIB		0x0C

template<class T>
class LoadCommandParser
{
private:

public:
	std::vector<LoadSegmentCommand <T> > segment_cmds;
	std::vector<LoadDyLibCommand> lib_cmds;
	/* More load command vectors here */

	LoadCommandParser(FILE *f, uint32_t n_cmds);
};

template<class T>
LoadCommandParser<T>::LoadCommandParser(FILE *file, uint32_t n_cmds)
{
	uint32_t cmd;

	for (uint32_t i = 0; i < n_cmds; i++) {
		FileUtils::readUint32(file, &cmd);
		if (cmd == LC_SEGMENT || cmd == LC_SEGMENT_64) {
		segment_cmds.push_back(LoadSegmentCommand<T>(file));
	} else if(cmd == LC_LOAD_DYLIB) {
		lib_cmds.push_back(LoadDyLibCommand(file));
	}
		else {
			FileUtils::readUint32(file, &cmd);
			fseek(file, cmd - 8, SEEK_CUR);
		}
	}
}
