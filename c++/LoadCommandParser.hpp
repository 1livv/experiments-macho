#include <vector>
#include <stdio.h>
#include "LoadSegmentCommand.hpp"
#include "FileUtils.hpp"

#define LC_SEGMENT 	0x1
#define LC_SEGMENT_64 	0x19

template<class T>
class LoadCommandParser
{
private:

public:
	std::vector<LoadSegmentCommand <T> > segment_cmds;
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
		} else {
			FileUtils::readUint32(file, &cmd);
			fseek(file, cmd - 8, SEEK_CUR);
		}
	}
}
