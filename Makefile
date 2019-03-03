all:
	g++ -std=gnu++11 elf_reader.cpp elf_reader.h memory.cpp main.cpp -o psim -lelf -lm -w
