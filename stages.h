#ifndef STAGES_H
#define STAGES_H

#include "memory.h"

extern int PC = 1;

//на вход - память инструкций и регистров
//сигналы
//регистр после стадии и результат АЛУ
#if 0
b_register fetch(insn_data_memory &object, uint8_t IRWrite, uint8_t lorD, b_register t_register, uint32_t ALUOut)
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
			uint32_t rs = get_bits(instr, 15, 5);		
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

b_register memory(b_register execute_reg, insn_data_memory object, uint8_t WE)
{
b_register return_memory_reg;

	//if WE == 0 read from data/instr memory
	if(WE == 0)
	{
		uint32_t num_reg= execute_reg.f_reg;
		//get instruction
		return_memory_reg.f_reg =  get_register[num_reg];
	}
	else
	{
	}


return return_memory_reg;
} 

void write_back(b_register execute_reg, uint8_t WB_WE)
{
	//write to RegFile
	if(WB_WE == 1)
	{
		
	}

}


#endif

extern int PC_R;
extern int PC_DISP;

fetch_reg fetch(insn_data_memory &mem, int PC)
{
	
	fetch_reg return_reg;
	if(PC_R == 1)
		PC = PC+PC_DISP;
	else
		PC = PC+1;

	return_reg.set_reg( mem.get_instruction(PC) );

	return return_reg;
}

decode_reg decode(fetch_reg reg, Regfile &obj) 
{

	//create Control Unit
	struct CU_signals CU;
	//initialize control unit depend from instruction
	CU = control_unit(reg.get_reg());
	decode_reg return_reg;

	uint8_t	rs1 = get_bits(reg.get_reg(), 15, 5);
	uint8_t	rs2 = get_bits(reg.get_reg(), 20, 5);
	uint8_t	rd = get_bits(reg.get_reg(), 7, 5);
	uint16_t imm1 = get_bits(reg.get_reg(), 20, 11);
	uint32_t imm2 = get_bits(reg.get_reg(), 31, 1);

	uint32_t sgn = sign_extended(imm2);
	uint32_t rs1_val = obj.get_register(rs1);
	uint32_t rs2_val = obj.get_register(rs2);

	return_reg.set_reg(CU,rs1,rs2,rs1_val,rs2_val,rd);

}

execute_reg execute(decode_reg reg)
{
execute_reg return_reg;

	CU_signals get_CU = reg.get_CU_reg();

	uint8_t AluOp_sign = get_CU.AluOp;
	uint8_t mux_ex_sign = get_CU.mux_ex1;
	uint8_t conditional_sign = get_CU.conditional;

	uint8_t rs1_address = reg.RS1_reg();
	uint8_t rs1_value = reg.RS1_val_reg();
	uint8_t rs2_value = reg.RS2_val_reg();	
	uint16_t imm1_value = reg.Imm1_reg();
	uint32_t imm2_value = reg.Imm2_reg();
	uint32_t RD_reg = reg.RD_reg();

	if(

	//????????

	

	//????????

return return_reg;
}

memory_reg memory(execute_reg reg, insn_data_memory &mem)
{	
	CU_signals get_CU = reg.get_CU_reg();
	uint32_t get_alu_result = reg.ALUresult_reg();
	uint32_t RS1_val = reg.rs1_val_reg();

	uint8_t MEM_WE = get_CU.MEM_WE;
	uint32_t RD = mem.get_register(get_alu_result);
	if(MEM_WE == 1)
	   	mem.set_register(RS1_val, get_alu_result);	
	

	uint32_t RESULT_D;	
	if(mux_mem1 == 0)
		RESULT_D = RD;
	else
		RESULT_D = get_alu_result;
	
	memory_reg return_reg(get_CU, RESULT_D, reg.RD_reg());

	return return_reg;	
}

void write_back(memory_reg reg, Regfile &regfile)
{
	CU_signals get_CU = reg.get_CU_reg();
	uint8_t WB_WE_signal = get_CU.WB_WE;
	uint32_t WB_D = reg.mux_res();
	uint8_t WB_A = reg.RD_reg();

	if(WB_WE == 1)
		regfile.set_register(WB_A, WB_D);

}



#endif



