#ifndef __LOAD_SEGMENT_COMMAND_HPP
#define __LOAD_SEGMENT_COMMAND_HPP

#include <stdint.h>
#include <vector>
#include "Section.hpp"

template <class T>
class LoadSegmentCommand
{
private:
  char name[16];
  T vmaddr;
  T vmsize;
  T fileoff;
  T filesize;
  uint32_t maxprot;
	uint32_t initprot;
	uint32_t nsects;
	uint32_t flags;
  std::vector<Section <T> > sections;


public:

  /******getter***********/
  char *getName();
  T getVmAddr() ;
  T getVmSize();
  T getFileOffset();
  T getFileSize();
  uint32_t getMaxProt();
  uint32_t getInitProt();
  uint32_t getNsects();
  uint32_t getFlags();
  std::vector<Section <T> > getSections();

};

template <class T>
char * LoadSegmentCommand<T>::getName()
{
  return name;
}

template <class T>
T LoadSegmentCommand<T>::getVmAddr()
{
  return vmaddr;
}

template <class T>
T LoadSegmentCommand<T>::getVmSize()
{
  return vmsize;
}

template <class T>
T LoadSegmentCommand<T>::getFileOffset()
{
  return fileoff;
}

template <class T>
T LoadSegmentCommand<T>::getFileSize()
{
  return filesize;
}

template <class T>
uint32_t LoadSegmentCommand<T>::getMaxProt()
{
  return maxprot;
}

template <class T>
uint32_t LoadSegmentCommand<T>::getInitProt()
{
  return initprot;
}

template <class T>
uint32_t LoadSegmentCommand<T>::getNsects()
{
  return nsects;
}

template <class T>
uint32_t LoadSegmentCommand<T>::getFlags()
{
  return flags;
}

template <class T>
std::vector<Section <T> > LoadSegmentCommand<T>::getSections()
{
  return sections;
}

#endif
