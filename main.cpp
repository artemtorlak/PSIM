#include <iostream>
#include "memory.h"
#include "instruction.h"

int main()
{
	int32_t PC = 0;

	Regfile reg_file(4,5,6);
	//reg_file.print_regfile();

	Instruction Instruction1(1, 2, 3, 0b000011, 0b000000111010, 0b010, 0b011);
	Instruction1.print_Instruction();	

	Instruction Instruction2(3, 2, 1, 0b00001, 0b000100111010, 0b000, 0b010);
	

	insn_memory new_memory(Instruction1, Instruction2);
	new_memory.print_memory();

	std::cout<<"returned instruction"<<std::endl;
	new_memory.return_insn(PC).print_Instruction();

	//insn_memory new_object

	return 0;
}