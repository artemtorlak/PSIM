#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include "instruction.h"

uint32_t sign_extend(uint16_t param)
{
	uint32_t sign_extended = param >> 15;
	uint32_t tmp = sign_extended*0xFFFF0000;
	return tmp || param;
	//uint16_t shift = 0b1000000000000000;
	
}

uint32_t alu(int control, uint32_t a, uint32_t b)
{
	switch(control)
	case 0: return a + b;
	case 1: return a*b;
	case 2: return a/b;
	case 3: return a-b;
}



class insn_memory{

	std::vector<Instruction> mem;

	public:

	insn_memory(Instruction Instruction1, Instruction Instruction2)
	{
		mem.push_back(Instruction1);
		mem.push_back(Instruction2);
	}

	Instruction return_insn(int32_t pc)
	{
		return mem[pc];
	}

	void print_memory()
	{
		for(auto i : mem) {
			i.print_Instruction();
		}
	}
	
};

class Regfile
{
	uint32_t m_regs[5];

  	public:
	Regfile(uint32_t a1, uint32_t a2, uint32_t a3)
	{
		m_regs[0] = a1;
		m_regs[1] = a2;
		m_regs[2] = a3;
	}
	

	//RD1 or RD2
	int32_t get_register(int number)
	{
		return m_regs[number];
	}

	//using A3 - index put m_regs[A3] = WD3;
	void set_register(int A3, uint32_t WD3)
	{
		m_regs[A3] = WD3;
	}

	void print_regfile()
	{
		for(int i =0; i < 5; ++i)
		{
			std::cout<<m_regs[i]<<std::endl;
		}
	}
	
};





#endif
