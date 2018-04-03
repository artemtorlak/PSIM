#ifndef STAGES_H
#define STAGES_H

#include "memory.h"

extern int PC = 1;

//на вход - память инструкций и регистров
//сигналы
//регистр после стадии и результат АЛУ

b_register fetch(insn_data_memory object, uint8_t IRWrite, uint8_t lorD, b_register t_register, uint32_t ALUOut)
{
	//get needed instrctuion
	if(IRWrite == 1)
	{
		//if signal irwirte == 1 , write to register instruction
		t_register.f_reg = object.get_instruction(PC);
	}
	else
	{}
	
	//to determint what to take : instruction or
	// result of sum ALU ( imm + rs)
	if(lorD == 1)
	{	
		t_register.sec_reg = object.get_instruction(ALUOut);
	}
	else
	{
		t_register.sec_reg = object.get_instruction(PC);
	}


return t_register;
}		 

//RegWrite signal
//new_regfile to read registers from regfile
b_register decode(b_register fetch_register, uint8_t RegWrite, Regfile regfile)
{
//get instruction from b_register of fetch stage
uint32_t instr = fetch_register.f_reg; 
b_register return_decode_reg;

	//If RegWrite == 0 only read from register file(rs1 for example)
	if(RegWrite == 0)
		{
			//take 5 rs bits
			uint32_t rs = get_bits(instr, 4, 3);		
			//take immidiate
			uint32_t imm = sign_extend(instr);
			return_decode_reg.f_reg = rs;
			return_decode_reg.sec_reg = imm;			
		}	
	else
		{
			//count number of rd register
			uint32_t rd = get_bits(instr,7,5);
			//write to regfile[rd register] word 
			//counted from aluout in stage fetch
			regfile.set_register(rd, fetch_register.sec_reg);			
		}

return return_decode_reg;
}

b_register execute(b_register decode_reg, uint8_t ALUSrcA, uint8_t ALUSrcB, uint8_t ALUControl, int PC)
{
b_register return_execute_reg;
	if(ALUSrcA == 0)
	{
		uint32_t alu_result = alu(0,PC,1);
		return_execute_reg.f_reg = alu_result;
	}
	else
	{
		uint32_t alu_result = alu(0, decode_reg.f_reg,decode_reg.s_reg); 
		return_execute_reg.f_reg = alu_result;
	}


return return_execute_reg;
}


void write_back(b_register execute_reg, uint8_t lorD)
{
	if(lorD == 1)
	{
		
	}



}






#endif


