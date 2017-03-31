#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "types.h"

#define MAGIC_32 0xFEEDFACE
#define MAGIC_64 0xFEEDFACF

#define LOAD_SEG_32 0x01
#define LOAD_SEG_64 0x19


#define read_uint_32(fd, buf)	\
	rc = read(fd, buf, 4);	\
	if(rc != 4)	\
		return 1

#define read_uint_64(fd, buf)	\
	rc = read(fd, buf, 8);	\
	if(rc != 8)	\
		return 1;

#define read_name(fd, buf)	\
	rc = read(fd, buf, 16);	\
		if(rc != 16)	\
			return 1;

int  extract_header(int fd, struct mach_header *header )
{
	int rc;
	read_uint_32(fd, &header->magic);

	if (header->magic != MAGIC_32 && header->magic != MAGIC_64)
		return 2;

	if (header->magic == MAGIC_32)
		header->is_32 = 1;
	else
		header->is_32 = 0;

	read_uint_32(fd, &header->cputype);

	read_uint_32(fd, &header->cpusubtype);

	read_uint_32(fd, &header->filetype);

	read_uint_32(fd, &header->ncmds);

	read_uint_32(fd, &header->sizeofofcmds);

	read_uint_32(fd, &header->flags);

	if (!header->is_32)
		read_uint_32(fd, &header->reserved);

	return 0;

}

void print_header(struct mach_header header)
{
	if (header.magic == MAGIC_32)
		printf("MACH-O 32\n");
	else
		printf("MACH-O 64\n");

	printf("cputype:%x\n subtype:%x\n filetype:%x\n ncmds:%x\n size:%d\n flags:%x\n", header.cputype,
	header.cpusubtype, header.filetype, header.ncmds, header.sizeofofcmds, header.flags);

	if (header.magic == MAGIC_64)
		printf("reserved%x\n", header.reserved);
}


int extract_segment_64(int fd, struct load_segment_command_64 *load_command)
{
	int index, rc;
	uint32_t command;
	uint32_t size;

	read_uint_32(fd, &command);
	read_uint_32(fd, &size);

	if(command != LOAD_SEG_64) {
		lseek(fd, size - 8, SEEK_CUR);
		return 2;
	}

	read_name(fd, load_command->name);

	read_uint_64(fd, &load_command->vmaddr);

	read_uint_64(fd, &load_command->vmsize);

	read_uint_64(fd, &load_command->fileoff);

	read_uint_64(fd, &load_command->filesize);

	read_uint_32(fd, &load_command->maxprot);

	read_uint_32(fd, &load_command->initprot);

	read_uint_32(fd, &load_command->nsects);

	read_uint_32(fd, &load_command->flags);

	if(load_command->nsects > 0)
		load_command->sections = malloc(load_command->nsects * sizeof(struct section_64));

	for(index = 0; index < load_command->nsects; index++) {
		read_name(fd, &load_command->sections[index].sectionname)
		read_name(fd, &load_command->sections[index].segmentname);

		read_uint_64(fd, &load_command->sections[index].addr);
		read_uint_64(fd, &load_command->sections[index].size);

		read_uint_32(fd, &load_command->sections[index].offset);
		read_uint_32(fd, &load_command->sections[index].align);
		read_uint_32(fd, &load_command->sections[index].relocations_offset);
		read_uint_32(fd, &load_command->sections[index].number_relocations);
		read_uint_32(fd, &load_command->sections[index].flags);
		read_uint_32(fd, &load_command->sections[index].reserved1);
		read_uint_32(fd, &load_command->sections[index].reserved2);
		read_uint_32(fd, &load_command->sections[index].reserved3);
	}

	return 0;

}

void print_section_64(struct section_64 sect) {

	printf("sectionName:%s\t segmentname:%s\n", sect.sectionname, sect.segmentname);
	printf("addr:0x%llx\t size:0x%llx\t offset:%d\t align:%d\n", sect.addr,
	sect.size, sect.offset, sect.align);

	printf("relocations_off:0x%x\t number:%d\n", sect.relocations_offset,
	sect.number_relocations);

	printf("flags:0x%x\n", sect.flags);
	printf("reserved1:0x%x\t reserved2:0x%x\t reserved3:0x%x\n", sect.reserved1,
	sect.reserved2, sect.reserved3);

	printf("\n\n");

}

void print_load_segment_64(struct load_segment_command_64 cmd) {

	int index = 0;

	printf("name:%s\n", cmd.name);
	printf("vmaddr:%llx\n vmsize:%llx\n", cmd.vmaddr, cmd.vmsize);
	printf("fileoff:%llu\n filesize:%llu\n", cmd.fileoff, cmd.filesize);
	printf("maxprot:%x\n initprot%x\n", cmd.maxprot, cmd.initprot);
	printf("nsects:%d\n flags:%x\n", cmd.nsects, cmd.flags);

	for(index = 0; index < cmd.nsects; index++)
		print_section_64(cmd.sections[index]);

}

int main(int argc, char *argv[])
{
	int index;
	int fd = open(argv[1], O_RDONLY);
	if(fd != 0)
		printf("opened the file\n");

	struct mach_header header;

	int rc = extract_header(fd, &header);
	if (rc != 0) {
		printf("simethin wrong happende %d\n", rc);
		return 0;
	}

print_header(header);

for(index = 0; index < header.ncmds; index++) {
	struct load_segment_command_64 command;
	int rc = extract_segment_64(fd, &command);

	if( rc == 0)
		print_load_segment_64(command);
	if(rc == 2)
		printf("skipped command\n");

	if(rc == 1) {
		printf("somethign wrong with the file\n");
		return 0;
	}

}

return 0;

}
