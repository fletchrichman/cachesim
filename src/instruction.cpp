//Determine type of instruction and its details as it is fetched
#include "instruction.h"

char Instruction::opcodeSymbol[] = {'L','S','B','C'};
void Instruction::SetOpcode(opcode op){
	m_opcode = op;
}

Instruction::opcode Instruction::GetOpcode(){
	return m_opcode;
}

void Instruction::SetInstrNum(uint64 instrNum){
	m_instrNum = instrNum;
}

uint64 Instruction::GetInstrNum(){
	return m_instrNum;
}

void Instruction::SetPc(uint32 pc){
	m_pc = pc;
}

uint32 Instruction::GetPc(){
	return m_pc;
}

void Instruction::SetExecInfo(uint32 exInfo){
	switch (m_opcode){
		case O_Load:
		case O_Store:
			m_exInfo.ldstAddr = exInfo;
			break;
		case O_Branch:
			m_exInfo.brTaken = exInfo;
			break;
		case O_Computation:
			m_exInfo.compLatency = exInfo;
			break;
		default:
			break;
	}
}

uint32 Instruction::GetExecInfo(){
	switch (m_opcode){
		case O_Load:
		case O_Store:
			return m_exInfo.ldstAddr;
			break;
		case O_Branch:
			return 1;
			break;
		case O_Computation:
			return m_exInfo.compLatency;
			break;
		default:
			return m_exInfo.ldstAddr;
			break;
	}
	return 0;
}






