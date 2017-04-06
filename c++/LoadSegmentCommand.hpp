#ifndef __LOAD_SEGMENT_COMMAND_HPP
#define __LOAD_SEGMENT_COMMAND_HPP

#include <stdint.h>
#include <vector>
#include <stdio.h>
#include "Section.hpp"
#include "FileUtils.hpp"

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
	LoadSegmentCommand(FILE *f);

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
LoadSegmentCommand<T>::LoadSegmentCommand(FILE *file)
{
	uint32_t cmdsize;
	uint32_t readsize = sizeof(T);

	FileUtils::readUint32(file, &cmdsize);
	fread(name, 16, 1, file);
	fread(&vmaddr, readsize, 1, file);
	fread(&vmsize, readsize, 1, file);
	fread(&fileoff, readsize, 1, file);
	fread(&filesize, readsize, 1, file);
	FileUtils::readUint32(file, &maxprot);
	FileUtils::readUint32(file, &initprot);
	FileUtils::readUint32(file, &nsects);
	FileUtils::readUint32(file, &flags);

	for (uint32_t i = 0; i < nsects; i++) {
		sections.push_back(Section<T>(file));
	}
}

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
