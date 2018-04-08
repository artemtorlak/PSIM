#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <bitset>

uint32_t multiplexor4(uint8_t rs1_addr, uint16_t imm1, uint32_t imm2, uint8_t RD, uint8_t mux_ex_signal)
{
	switch(mux_ex_signal)
	case 0: return rs1_addr;
	case 1: return imm1;
	case 2: return imm2;
	case 3: return RD:
}

int8_t multiplexor(int8_t lorD)
{
	if(lorD == 0)
		return 0;
	else
		return 1;
}

//uint8_t multiplexor

struct CU_signals
{
	uint8_t WB_WE = 0
	uint8_t MB_WE = 0;
	uint8_t mux_ex1 = 0;
	uint8_t AluOp = 0;
	uint8_t mux_mem1 = 0;
	uint8_t conditional = 0;

	CU_signals()
	{}

	void set_sginals(uint8_t WB_WE_val, uint8_t MB_WE_val, uint8_t mux_ex1_val,
		uint8_t AluOp_val, uint8_t mux_mem1, uint8_t conditional_val)
	{
		WB_WE = WB_WE_val;
		MB_WE = MB_WE_val;
		mux_ex1 = mux_ex1_val;
		AluOp = AluOp_val;
		mux_mem1 = mux_mem1_val;
		conditional = conditional_val;
	}
}

CU_signals control_unit(uint32_t insn) //uint8_t oppcode, uint8_t funct7)
{
	uint8_t oppcode = get_bits(insn, 0, 7);
	uint8_t funct7 = get_bits(insn, 25, 7);

	CU_signals get_signals;

	//R-type
	if(oppcode == 0b0110011)
	{
		//if funct7 = 01 - substitution , AluOp = 1
		switch(funct7)
		case 0b0100000 : get_signals.set_sginals(1,0,0,1,1,0)
		case 0b0000000 : get_signals.set_sginals(1,0,0,0,1,0)
	}
	
	if(oppcode == 0b0000011)
	{
		case 0b0100000 : get_signals.set_sginals(1,0,1,0,0,0)
	}
	
	if(oppcode == 0b0100011)
	{
		case 0b0100000 : get_signals.set_sginals(0,1,2,0,0,0)
	}
	
	if(oppcode == 0b1100011)
	{
		//if funct7 = 01 - substitution , AluOp = 1
		case 0b0100000 : get_signals.set_sginals(0,0,0,0,0,1)
	}

return get_sginals;
}


class fetch_reg
{
	uint32_t reg;

	public:

	void set_reg(uint32_t val)
	{	
		reg = val;
	}

	uint32_t get_reg()
	{
		return reg;
	}

	void print_reg()
	{
		std::cout<<"fetch_reg: "<<std::bitset<32>(reg)<<std::endl;	
	}
}

class decode_reg
{
	CU_signals CU_reg;
	uint8_t RS1;
	uint8_t RS2;
	uint32_t RS1_val;
	uint32_t RS2_val
	//from 20 to 30
	uint16_t imm1;
	//31
	uint32_t imm2;
	uint8_t RD;

	public:
	void set_reg(CU_signals CU_reg_val, uint8_t RS1_v, uint8_t RS2_v, uint32_t RS1_vv, uint32_t RS2_vv, uint8_t RD_v, uint16_t imm1_val, uint32_t imm2_val)
	{
		CU_reg = CU_reg_val;
		RS1 = RS1_v;
		RS2 = RS2_v;
		RS1_val = RS1_vv;
		RS2_val = RS2_vv;
		imm1 = imm1_val;
		imm2 = imm2_val;
		RD = RD_v;
	}


	CU_signals get_CU_reg()
	{
		return CU_reg;
	}	

	uint8_t RS1_reg()
	{
		return RS1;
	}	

	uint8_t RS2_reg()
	{
		return RS2;
	}

	uint32_t RS1_val_reg()
	{
		return RS1_val;
	}	

	uint32_t RS2_val_reg()
	{
		return RS2_val;
	}

	uint8_t RD_reg()
	{
		return RD;
	}

	uint16_t Imm1_reg()
	{
		return imm1;
	}


	uint32_t Imm2_reg()
	{
		return imm2;
	}
}

class execute_reg
{
	CU_signals CU_reg;
	uint8_t rs1;
	uint32_t rs1_val;
	uint32_t ALUresult;
	uint8_t RD;

	execute_reg(CU_signals CU_val, uint8_t rs1_v, uint32_t rs1_vv, uint32_t ALUresult_val, uint8_t RD_val)
	{
		CU_reg = CU_val;
		rs1 = rs1_v;
		rs1_val = rs1_vv;
		ALUresult = ALUresult_val;
		RD = RD_val;
	}

	CU_signals CU_r()
	{
		return CU_reg;
	}

	uint8_t rs1_reg()
	{
		return rs1;
	}


	uint32_t rs1_val_reg()
	{
		return rs1_val;
	}


	uint32_t ALUresult_reg()
	{
		return ALUresult;
	}


	uint8_t RD_reg()
	{
		return RD;
	}
}

class memory_reg
{
	CU_signals CU_reg;
	uint32_t mux_result;
	uint8_t RD;

	memory_reg(CU_signals CU_reg_val,uint32_t mux_result_val,uint8_t RD_val)
	{
		CU_reg = CU_reg_val;
		mux_result = mux_result_val;
		RD = RD_val;
	}

	CU_signals get_CU()
	{
		return CU_reg;
	}

	uint32_t mux_res()
	{
		return mux_result;
	}

	uint8_t RD_reg()
	{
		return RD;
	}

}

/*
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
*/

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

	void set_register(uint32_t reg, uint32_t A)
	{
		m_regs[A] = reg;
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
