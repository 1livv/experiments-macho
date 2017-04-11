build: header_cpp

header_cpp: MachHeader.o FileUtils.o main.o LoadDyLibCommand.o LoadSegmentCommand.hpp.gch
		g++  MachHeader.o FileUtils.o main.o LoadDyLibCommand.o -o header_cpp
MachHeader.o:	MachHeader.cpp
		g++ -c MachHeader.cpp

FileUtils.o: FileUtils.cpp
	g++ -c FileUtils.cpp

LoadDyLibCommand.o: LoadDyLibCommand.cpp
	g++ -c LoadDyLibCommand.cpp

LoadSegmentCommand.hpp.gch: LoadSegmentCommand.hpp
	g++ -c LoadSegmentCommand.hpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm MachHeader.o FileUtils.o main.o header_cpp LoadDyLibCommand.o LoadSegmentCommand.hpp.gch
