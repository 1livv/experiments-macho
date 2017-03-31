#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>


struct mach_header {
	int is_32;
	uint32_t magic;
	uint32_t cputype;
	uint32_t cpusubtype;
	uint32_t filetype;
	uint32_t ncmds;
	uint32_t sizeofofcmds;
	uint32_t flags;
	uint32_t reserved;
};

struct load_segment_command_32 {
	char name[16];
	uint32_t vmaddr;
	uint32_t vmsize;
	uint32_t fileoff;
	uint32_t filesize;
	uint32_t maxprot;
	uint32_t initprot;
	uint32_t nsects;
	uint32_t flags;
};

struct load_segment_command_64 {
	char name[16];
	uint64_t vmaddr;
	uint64_t vmsize;
	uint64_t fileoff;
	uint64_t filesize;
	uint32_t maxprot;
	uint32_t initprot;
	uint32_t nsects;
	uint32_t flags;
	struct section_64 *sections;

};

struct section_64 {
	char sectionname[16];
	char segmentname[16];
	uint64_t addr;
	uint64_t size;
	uint32_t offset;
	uint32_t align;
	uint32_t relocations_offset;
	uint32_t number_relocations;
	uint32_t flags;
	uint32_t reserved1;
	uint32_t reserved2;
	uint32_t reserved3;
};
