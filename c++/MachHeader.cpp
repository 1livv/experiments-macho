#include "MachHeader.hpp"
#include "FileUtils.hpp"

MachHeader::MachHeader(FILE *file)
{
  FileUtils::readUint32(file, &magic);

  if(magic != MAGIC_32 && magic != MAGIC_64)
  {
    //throw exception
    return;
  }

  if(magic == MAGIC_32)
    is_32 = true;
  else
    is_32 = false;

  FileUtils::readUint32(file, &cputype);
  FileUtils::readUint32(file, &cpusubtype);
  FileUtils::readUint32(file, &filetype);
  FileUtils::readUint32(file, &ncmds);
  FileUtils::readUint32(file, &sizeofofcmds);
  FileUtils::readUint32(file, &flags);

  if(!is_32)
    FileUtils::readUint32(file, &reserved);

}
bool MachHeader::getIs32()
{
  return is_32;
}

uint32_t MachHeader::getMagic()
{
  return magic;
}

uint32_t MachHeader::getCpuType()
{
  return cputype;
}

uint32_t MachHeader::getCpuSubType()
{
  return cpusubtype;
}

uint32_t MachHeader::getFileType()
{
  return filetype;
}

uint32_t MachHeader::getNcmds()
{
  return ncmds;
}

uint32_t MachHeader::getSizeOfCmds()
{
  return sizeofofcmds;
}

uint32_t MachHeader::getFlags()
{
  return flags;
}

uint32_t MachHeader::getReserved()
{
  if(!is_32)
    return reserved;

  //throws exception
  return -1;
}
