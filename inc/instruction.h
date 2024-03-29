#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "types.h"

class Instruction{
public:
	enum opcode {
		O_MinimumValue = 0,
		O_Load = 0,
		O_Store,
		O_Branch,
		O_Computation,
		O_NumValues,
		O_InvalidValue
	};

	typedef union {
		uint32 ldstAddr;
		uint32 compLatency;
		uint32 brTaken;

	} executionInfo;

	void SetExecInfo(uint32 exInfo);
	uint64 GetInstrNum();
	void SetInstrNum(uint64 instrNum);
	static char opcodeSymbol[];
	opcode GetOpcode();
	void SetOpcode(opcode op);
	uint32 GetPc();
	void SetPc(uint32 pc);
	uint32 GetExecInfo();


private:
	uint64 m_instrNum;
	opcode m_opcode;
	uint32 m_pc;
	executionInfo m_exInfo;
};

#endif