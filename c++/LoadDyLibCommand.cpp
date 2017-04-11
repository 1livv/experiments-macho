#include "FileUtils.hpp"
#include "LoadDyLibCommand.hpp"

#include <stdlib.h>

LoadDyLibCommand::LoadDyLibCommand(FILE *file)
{
  uint32_t cmdsize, name_offset;

  FileUtils::readUint32(file, &cmdsize);
  FileUtils::readUint32(file, &name_offset);

  FileUtils::readUint32(file, &timestamp);
  FileUtils::readUint32(file, &current_version);
  FileUtils::readUint32(file, &compatibility_version);

  name = (char *)malloc(cmdsize - name_offset);
  FileUtils::readBytes(file, name, cmdsize - name_offset);

}

uint32_t LoadDyLibCommand::getTimestamp()
{
  return timestamp;
}

uint32_t LoadDyLibCommand::getCurrentVersion()
{
  return current_version;
}

uint32_t LoadDyLibCommand::getCompatibilityVersion()
{
  return compatibility_version;
}

char * LoadDyLibCommand::getName()
{
  return name;
}
