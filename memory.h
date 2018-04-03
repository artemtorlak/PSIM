#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <bitset>

int8_t multiplexor(int8_t lorD)
{
	if(lorD == 0)
		return 0;
	else
		return 1;
}

uint8_t multiplexor

class b_register
{

	public:

	uint32_t f_reg;
	uint32_t sec_reg;
	uint32_t t_reg;
	uint32_t fth_reg;

	b_register()
	{}

	b_register (uint32_t reg1, uint32_t reg2)
	{
		f_reg = reg1;
		sec_reg = reg2;
	}

	void print_reg()
	{
			std::cout<<"instr_reg: "<<std::bitset<32>(f_reg)<<std::endl;
			std::cout<<"data_reg: "<<std::bitset<32>(sec_reg)<<std::endl;
			std::cout<<std::endl;
	}
};

uint32_t get_bits(uint32_t insn, unsigned int pos, unsigned int n )
{
    	return ((insn & (~( ~0 << n ) << pos))>>pos);

}   

int32_t sign_extend(uint32_t insn)
{
	std::cout<<"instrusction"<<std::bitset<32>(insn)<<std::endl;
	uint16_t number_register = insn>>20;
	//std::cout <<std::bitset<16>(number_register) <<std::endl;
	uint32_t tmp = 0;	
	uint8_t get_higher_bit = number_register >> 11;
	//std::cout<<std::bitset<8>(get_higher_bit)<<std::endl;
	if(get_higher_bit == 1)
		 tmp = number_register | 0xFFFFF000;
	else
		 tmp = number_register;

	return tmp;
}


int32_t alu(int ALUOp, uint32_t a, uint32_t b)
{
	switch(ALUOp)
	{
		case 0: return a + b;
		case 1: return a - b;
		case 2: return a/b;
		case 3: return a-b;
	}
}


//класс instn_Memory - хранит массив из 32 битных инструкций
class insn_data_memory {

	std::vector<uint32_t> insn;
	uint32_t m_regs[32];

	public:
	insn_data_memory()
	{
	}
	
	insn_data_memory(uint32_t a1, uint32_t a2)
	{
		m_regs[0] = a1;
		m_regs[1] = a2;
	}	

	void set_instr(uint32_t obj)
	{
		insn.push_back(obj);
	}

	uint32_t get_instruction(int PC)
	{
		return insn[PC];
	}

	uint32_t get_register(uint32_t reg)
	{
		return m_regs[reg];
	}

	void print_instruction(uint32_t PC)
	{
		std::cout<<"oppcode :"<<std::bitset<7>(insn[PC]&0b1111111)<<std::endl;
		std::cout<<"rd :"<<std::bitset<5>((insn[PC]>>7)&0b11111)<<std::endl;	
		std::cout<<"rs1 :"<<std::bitset<5>((insn[PC]>>15)&0b11111)<<std::endl;
		std::cout<<"rs2 :"<<std::bitset<5>((insn[PC]>>20)&0b11111)<<std::endl;	
		
	}

	
};


class Regfile
{
	uint32_t m_regs[32];

  	public:
  	Regfile()
  	{}

	Regfile(uint32_t a1, uint32_t a2, uint32_t a3)
	{
		m_regs[0] = a1;
		m_regs[1] = a2;
		m_regs[20] = a3;
	}
	

	int32_t get_register(uint32_t number_register)
	{
		return m_regs[number_register];
	}

	void set_register(uint8_t number_register, uint32_t word)
	{
		m_regs[number_register] = word;
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
