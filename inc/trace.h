/*
 * trace.h
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#ifndef TRACE_H_
#define TRACE_H_

#include <stdio.h>
#include <string>

#include "instruction.h"
#include "results.h"

class Trace
{
public:
	static int OpenTraceFile(std::string filename);
	static int GetInstruction(Instruction* instr, Results* results);
	static void PrintInstruction(Instruction* instr);

private:
	static FILE* m_traceFile;
	static uint64 m_instrNum;
};

#endif /* TRACE_H_ */
