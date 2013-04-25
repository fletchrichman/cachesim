#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "instruction.h"
#include "results.h"
#include "Cache.h"

class Simulator {
public:
	static void HandleInstruction(Instruction* instr,Cache* L1I,Cache* L1D,Cache* L2,Results* results);
};
#endif
