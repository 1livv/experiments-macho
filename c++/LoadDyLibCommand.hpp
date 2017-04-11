#ifndef __LOAD_DYLIB_COMMAND_HPP
#define __LOAD_DYLIB_COMMAND_HPP

#include <stdio.h>
#include <stdint.h>


class LoadDyLibCommand
{
private:
  uint32_t timestamp;
  uint32_t current_version;
  uint32_t compatibility_version;
  char * name;

public:
  LoadDyLibCommand(FILE * file);
  /********geter**************/
  uint32_t getTimestamp();
  uint32_t getCurrentVersion();
  uint32_t getCompatibilityVersion();
  char * getName();

};


#endif
