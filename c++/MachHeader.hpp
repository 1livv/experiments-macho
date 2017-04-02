#ifndef __MACHHEADER_HPP
#define __MACHHEADER_HPP

#include <stdint.h>
#include <stdio.h>

#define MAGIC_32 0xFEEDFACE
#define MAGIC_64 0xFEEDFACF

class MachHeader
{
private:
  bool is_32;
  uint32_t magic;
  uint32_t cputype;
  uint32_t cpusubtype;
  uint32_t filetype;
  uint32_t ncmds;
  uint32_t sizeofofcmds;
  uint32_t flags;
  uint32_t reserved;

public:

  MachHeader(FILE *file);

  /****getter*******/
  uint32_t getIs32();
  uint32_t getMagic();
  uint32_t getCpuType();
  uint32_t getCpuSubType();
  uint32_t getFileType();
  uint32_t getNcmds();
  uint32_t getSizeOfCmds();
  uint32_t getFlags();
  uint32_t getReserved();

};

#endif
