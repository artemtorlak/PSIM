#include "memory.h"
#include "stages.h"
#include "elf_reader.h"
#include <bitset>
#include <iostream>

// INVITATION

int main() 
{


	//elf loader
	elf::Elf_reader er;
    
    er.Init("load_elf");
    std::vector<uint32_t> insns;
    
    uint32_t pc = 0, va;
    
    if (!er.Load(insns, va, pc))
    	std::cout<<"ERROR"<<std::endl;

    std::cout<<"CMD SIZE IS: "<<insns.size()<<std::endl;

	#if 0	
    std::vector<uint32_t> insns = {0b00000000010000011000000110110011, //add x3 , x3, x4
								   0b0000000 00011 00101 000 00100 1100011, // beq x3, x5, 2
								   0b1111111 00101 00101 000 11101 1100011,  //beq x5, x5, -2
								   0b00000000000000000000000001111111};
	#endif
	// global instruction and data memory
	//std::vector<uint32_t> insns = {0b11110111000000010000000100010011};	
	Insn_data_memory instr_data_mem;
	instr_data_mem.set_insn(insns);
	instr_data_mem.print_memory();

	// global regfile
	uint32_t regs[32] = {0, 2, 0, 0, 1, 1000, 10, 7, 3, 7, 4, 6, 2, 6, 2, 5, 3, 6, 2, 7, 6, 4, 2, 6, 9, 3, 3, 0, 8, 4, 5, 3};
	Regfile regfile(regs);
	regfile.print_regfile();

	// global signals
	uint32_t PC = 0;
	uint32_t PC_DISP = 0;
	uint8_t PC_R = 0;
	uint32_t BP_EX = 0;
	uint32_t BP_MEM = 0;
	uint32_t local_PC = 0;
	uint8_t branch = 0;

	Fetch_reg fetch_reg;
	Decode_reg decode_reg;
	Execute_reg execute_reg;
	Memory_reg memory_reg;
	HU HazardUnit;

	int N = 6000;
	 // number of cycles
	for (int i = 0; i < N; i++) {
		printf("--------------------------------------------------------\n");
		//std::cout << "PC = " << PC << std::endl;
		std::cout << "cycle = " << i << std::endl;

		//Fetch stage
		//After this stage we get int time_
		Fetch_reg fetch_tmp = fetch(instr_data_mem, PC, PC_DISP, PC_R, local_PC, branch); 
		fetch_tmp.print_reg();

		//Decode stage
		Decode_reg decode_tmp = decode(fetch_reg, regfile, HazardUnit);
		decode_tmp.print_reg();

		Execute_reg execute_tmp = execute(decode_reg, PC_DISP, PC_R, BP_EX, BP_MEM, local_PC, branch, HazardUnit);
		execute_tmp.print_reg();

		Memory_reg memory_tmp = memory(execute_reg, instr_data_mem, BP_EX, branch, HazardUnit);
		memory_tmp.print_reg();

		write_back(memory_reg, regfile, BP_MEM, branch, HazardUnit);

		HazardUnit.Run(fetch_tmp, decode_tmp, execute_tmp, memory_tmp);

		fetch_reg = execute_tmp.GetFlush() ? Fetch_reg() : fetch_tmp;
		decode_reg = execute_tmp.GetFlush() ? Decode_reg() : decode_tmp;
		execute_reg = execute_tmp;
		memory_reg = memory_tmp;
		
	}

	return 0;
}
