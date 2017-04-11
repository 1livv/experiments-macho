#include <stdio.h>
#include <stdint.h>
#include "MachHeader.hpp"
#include "LoadCommandParser.hpp"

template<class T>
void print_segments(LoadCommandParser<T> parser)
{
	puts("== Segments ==");
	for (uint32_t i = 0;  i < parser.segment_cmds.size(); i++) {
		printf("Name:\t\t%s\n", parser.segment_cmds[i].getName());
		printf("vmaddr:\t\t%p\n", parser.segment_cmds[i].getVmAddr());
		printf("vmsize:\t\t%lu\n", (uint64_t) parser.segment_cmds[i].getVmSize());
		printf("fileoff:\t%p\n", parser.segment_cmds[i].getFileOffset());
		printf("filesize:\t%lu\n", (uint64_t) parser.segment_cmds[i].getFileSize());
	}
	puts("--------");
}

template<class T>
void print_libraries(LoadCommandParser<T> parser)
{
	puts("== Libraries ==");

	for(uint32_t i = 0; i < parser.lib_cmds.size(); i++)
		puts(parser.lib_cmds[i].getName());
}

void print_header(MachHeader header)
{
	if (header.getMagic() == MAGIC_32)
		printf("MACH-O 32\n");
	else
		printf("MACH-O 64\n");

	printf("cputype:%d\n subtype:%x\n filetype:%x\n ncmds:%d\n size:%d\n flags:%x\n", header.getCpuType(),
			header.getCpuSubType(), header.getFileType(), header.getNcmds(), header.getSizeOfCmds(), header.getFlags());

	if (header.getMagic() == MAGIC_64)
		printf("reserved%x\n", header.getReserved());
}

int main(int argc, char *argv[])
{
	FILE *file;

	if (argc != 2) {
		printf("Usage: %s <binary>\n", argv[0]);
		return -1;
	}

	file = fopen(argv[1], "rb");
	if(!file)
	{
		printf("file not opened");
		return 0;
	}

	MachHeader header(file);
	print_header(header);
	if (header.getMagic() == MAGIC_32) {
		LoadCommandParser<uint32_t> lcp(file, header.getNcmds());
		print_segments(lcp);
		print_libraries(lcp);
	}
	if (header.getMagic() == MAGIC_64) {
		LoadCommandParser<uint64_t> lcp(file, header.getNcmds());
		print_segments(lcp);
		print_libraries(lcp);
	}
	return 0;
}
