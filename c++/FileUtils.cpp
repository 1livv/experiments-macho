#include "FileUtils.hpp"

void FileUtils::readUint32(FILE *file, uint32_t *buff)
{
  fread(buff, sizeof(uint32_t), 1, file);
}
