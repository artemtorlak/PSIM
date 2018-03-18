#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <sys/types.h>

class Instruction
{
	uint8_t rs1, rs2, rd;
	uint16_t oppcode;
	uint32_t imm;
	uint16_t funct7;
	uint8_t funct3;

	public:

	Instruction(uint8_t r_rs1, uint8_t r_rs2, uint8_t r_rd, uint16_t r_oppcode, uint32_t r_imm, uint16_t r_funct7, uint8_t r_funct3)
	{
		rs1 = r_rs1;
		rs2 = r_rs2;
		rd = r_rd;
		oppcode = r_oppcode;
		imm = r_imm;
		funct7 = r_funct7;
		funct3 = r_funct3;
	}

	void print_Instruction()
	{
		std::cout<<unsigned(rs1)<<std::endl;
		std::cout<<unsigned(rs2)<<std::endl;
		std::cout<<unsigned(rd)<<std::endl;
		std::cout<<oppcode<<std::endl;
		std::cout<<imm<<std::endl;
		std::cout<<funct7<<std::endl;
		std::cout<<unsigned(funct3)<<std::endl;
	}
};


#endif
