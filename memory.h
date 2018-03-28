#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <bitset>


int32_t sign_extend(uint32_t insn)
{
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
class insn_memory {

	std::vector<uint32_t> insn;

	public:

	insn_memory(uint32_t obj)
	{
		insn.push_back(obj);
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
	Regfile(uint32_t a1, uint32_t a2, uint32_t a3)
	{
		m_regs[0] = a1;
		m_regs[1] = a2;
		m_regs[20] = a3;
	}
	

	//A1,A2
	//подаем инструкцию, номер бита (from) , получаем начиная с from 5 бит.
	//эти 5 бит - номер регистра, далее считываем из массива регистров m_regs[number]  
	int32_t get_register(uint32_t insn, int from)
	{
		uint8_t number_register = (insn>>from)&0b11111;
		return m_regs[number_register];
	}

	//A3
	//кладем результат от rs1 и rs2 в rd.
	void set_register(uint32_t insn, uint32_t WD3)
	{
		//получаем номер rd, потом в rd кладем WD3
	 	uint8_t number_register = (insn>>7)&0b11111;
		m_regs[number_register] = WD3;
	}

	//m_regs[regfile]
	uint32_t data_memory(uint32_t aluresult)
	{
		return m_regs[aluresult];
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
