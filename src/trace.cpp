/*
 * trace.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#include "trace.h"
#include "config.h"

#include <stdlib.h>
#include <iostream>
#include <string.h>

#ifdef USE_STD_IN
#define READ_ACTION(...) scanf(__VA_ARGS__)
#else
#define READ_ACTION(...) fscanf(m_traceFile, __VA_ARGS__)
#endif

FILE* Trace::m_traceFile = NULL;
uint64 Trace::m_instrNum = 0;

using namespace std;

int Trace::OpenTraceFile(string filename)
{
	if(strcmp(filename.c_str(),"stdin")==0)
	{
		m_traceFile=stdin;
	}
	// Open the file, store it in file variable
	else
	{
		if((m_traceFile = fopen(filename.c_str(), "r")) == NULL)
		{
			return 1;
		}
	}
	m_instrNum = 0;

	return 0;
}

int Trace::GetInstruction(Instruction* instr, Results* results)
{
	char opType;
	uint32 pc;
	// Get operation type and program counter while checking for end of file
	if (READ_ACTION("%c %8x", &opType, &pc) == EOF)
	{
		return -1;
	}

	instr->SetPc(pc);

	uint32 exInfo;

	// Need to parse execution info differently for each operation type
	switch (opType)
	{
		case 'L':
			// Parse the address of load
			instr->SetOpcode(Instruction::O_Load);
			break;
		case 'S':
			// Parse the address of save
			instr->SetOpcode(Instruction::O_Store);
			break;
		case 'B':
			// Parse the 0/1 of whether branch is taken
			instr->SetOpcode(Instruction::O_Branch);
			break;
		case 'C':
			// Parse the number of clock ticks computation takes
			instr->SetOpcode(Instruction::O_Computation);
			break;
		default:
			instr->SetOpcode(Instruction::O_InvalidValue);
			break;
	}

	READ_ACTION("%8x ", &exInfo);
	instr->SetExecInfo(exInfo);
	instr->SetInstrNum(m_instrNum);
	m_instrNum++;

	results->ParsedInstruction(instr->GetOpcode());

	return 0;
}

void Trace::PrintInstruction(Instruction* instr)
{
	cout << endl << "Instruction " << instr->GetInstrNum()
		 << ": Opcode = " << Instruction::opcodeSymbol[instr->GetOpcode()]
		 << ", ExecInfo = " << instr->GetExecInfo()<<endl;
}

