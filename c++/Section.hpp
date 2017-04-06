#ifndef __SECTION_HPP
#define __SECTION_HPP

#include <stdint.h>
#include <stdio.h>
#include "FileUtils.hpp"

template <class T>
class Section
{
private:
	bool is_32;
	char sectionname[16];
	char segmentname[16];
	T addr;
	T size;
	uint32_t offset;
	uint32_t align;
	uint32_t relocations_offset;
	uint32_t number_relocations;
	uint32_t flags;
	uint32_t reserved1;
	uint32_t reserved2;
	uint32_t reserved3;

public:
	Section(FILE *);

	/****getter*********/
	bool getIs32();
	char * getSectionName();
	char * getSegmentName();
	T getAddr();
	T getSize();
	uint32_t getOffset();
	uint32_t getAlign();
	uint32_t getRelocationOffset();
	uint32_t getNumberofRelocations();
	uint32_t getFlags();
	uint32_t getReserved1();
	uint32_t getReserved2();
	uint32_t getReserved3();
};

template <class T>
Section<T>::Section(FILE *file)
{
	uint32_t readsize = sizeof(T);

	fread(sectionname, 16, 1, file);
	fread(segmentname, 16, 1, file);
	fread(&addr, readsize, 1, file);
	fread(&size, readsize, 1, file);
	FileUtils::readUint32(file, &offset);
	FileUtils::readUint32(file, &align);
	FileUtils::readUint32(file, &relocations_offset);
	FileUtils::readUint32(file, &number_relocations);
	FileUtils::readUint32(file, &flags);
	FileUtils::readUint32(file, &reserved1);
	FileUtils::readUint32(file, &reserved2);
	FileUtils::readUint32(file, &reserved3);
}

template <class T>
bool Section<T>::getIs32()
{
	return is_32;
}

template <class T>
char * Section<T>::getSectionName()
{
	return sectionname;
}

template <class T>
char * Section<T>::getSegmentName()
{
	return segmentname;
}

template <class T>
T Section<T>::getAddr()
{
	return addr;
}

template <class T>
T Section<T>::getSize()
{
	return size;
}

template <class T>
uint32_t Section<T>::getOffset()
{
	return offset;
}

template <class T>
uint32_t Section<T>::getAlign()
{
	return align;
}

template <class T>
uint32_t Section<T>::getRelocationOffset()
{
	return relocations_offset;
}

template <class T>
uint32_t Section<T>::getNumberofRelocations()
{
	return number_relocations;
}

template <class T>
uint32_t Section<T>::getFlags()
{
	return flags;
}

template <class T>
uint32_t Section<T>::getReserved1()
{
	return reserved1;
}

template <class T>
uint32_t Section<T>::getReserved2()
{
	return reserved2;
}

template <class T>
uint32_t Section<T>::getReserved3()
{
	if(!is_32)
	  return reserved3;
	//throw exception;
	return -1;
}



#endif
