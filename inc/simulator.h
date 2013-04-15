/*
 * simulator.h
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "instruction.h"
#include "results.h"
#include "cache.h"

class Simulator
{
public:
	static void HandleInstruction(Instruction* instr,
								  Cache* L1I,
								  Cache* L1D,
								  Cache* L2,
								  Results* results);
};


#endif /* SIMULATOR_H_ */
