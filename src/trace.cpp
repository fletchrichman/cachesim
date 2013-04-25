#include "trace.h"
#include "config.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>

FILE* Trace::m_traceFile = NULL;
uint64 Trace::m_instrNum = 0;
using namespace std;

int Trace::OpenTraceFile(string filename){
	if(strcmp(filename.c_str(),"stdin")==0) m_traceFile=stdin;
	else if((m_traceFile = fopen(filename.c_str(), "r")) == NULL) return 1;
	m_instrNum = 0;
	return 0;
}

int Trace::GetInstruction(Instruction* instr, Results* results){
	char opType;
	uint32 pc;
	//Get instruction info
	if (scanf("%c %8x", &opType, &pc) == EOF) return -1;
	instr->SetPc(pc);
	uint32 exInfo;
	switch (opType){
		case 'L':
			instr->SetOpcode(Instruction::O_Load);			//Load
			break;
		case 'S':
			instr->SetOpcode(Instruction::O_Store);			//Save
			break;
		case 'B':
			instr->SetOpcode(Instruction::O_Branch);		//Branch
			break;
		case 'C':
			instr->SetOpcode(Instruction::O_Computation);	//Computation time in ticks
			break;
		default:
			instr->SetOpcode(Instruction::O_InvalidValue);	//Invalid
			break;
	}

	scanf("%8x ", &exInfo);
	instr->SetExecInfo(exInfo);
	instr->SetInstrNum(m_instrNum);
	m_instrNum++;
	results->ParsedInstruction(instr->GetOpcode());
	return 0;
}

void Trace::PrintInstruction(Instruction* instr){
	cout << endl << "Instruction " << instr->GetInstrNum()
		 << ": Opcode = " << Instruction::opcodeSymbol[instr->GetOpcode()]
		 << ", ExecInfo = " << instr->GetExecInfo()<<endl;
}

