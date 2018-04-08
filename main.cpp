#include <iostream>
#include "memory.h"
#include "stages.h"

int main()
{


uint32_t insn = 0b011111100111000010000101000000000;
uint32_t insn2 =0b01000000100000001000101000011111;

//global instruction and data memory


insn_data_memory instr_data_mem;


instr_data_mem.set_instr(insn);
instr_data_mem.set_instr(insn2);

//global regfile
Regfile register_file;

while(1)
{
//signals
uint8_t IRWrite = 1;
uint8_t lorD = 0;
uint8_t RegWrite = 0;

b_register time_reg;
uint32_t ALUOut;
b_register fetch_reg;

b_register decode_reg;

//Fetch stage
//After this stage we get int time_
fetch_reg = fetch(&instr_data_mem, IRWrite, lorD, time_reg, ALUOut); execute_reg.s_reg;
fetch_reg.print_reg();

//Decode stage
decode_reg = decode(fetch_reg, RegWrite, register_file);
decode_reg.print_reg();

execute_reg = execute();
fetch_reg(execute_reg)

}
#if 0
insn_memory instr_memory(insn);
instr_memory.print_instruction(PC);

PC = alu(0,PC,1);

Regfile new_regfile(15,20,40);
//получаем значение RS1 
int32_t A1 = new_regfile.get_register(insn, 15);

std::cout<<"A1 is: "<<std::bitset<32>(A1)<<std::endl;

//получаем значение immidiate
int32_t imm = new_regfile.get_register(insn,20);

std::cout<<"Imm: "<<std::bitset<32>(imm)<<std::endl;

int32_t sign_extended_imm = sign_extend(insn);

std::cout<<"sign_extended_imm: "<<std::bitset<32>(sign_extended_imm)<<std::endl;

int32_t alu_result = alu(0,A1,sign_extended_imm);

std::cout<<"ALU result "<<std::bitset<32>(alu_result)<<std::endl;

uint32_t value_ = new_regfile.data_memory(alu_result);

std::cout<<"The data_memory of index[alu_result] "<<std::bitset<32>(value_)<<std::endl;

new_regfile.set_register(insn, value_);

new_regfile.print_regfile();

//std::cout<<std::bitset<32>(sign_extend(insn));
#endif

//insn_memory new_insn(insn);
//new_insn.print_instruction();


#if 0
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

#endif
	return 0;
}
