/*
 * results.h
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#ifndef RESULTS_H_
#define RESULTS_H_

#include "cache.h"
#include "instruction.h"

class Results
{
public:
	Results();
	void PrintResults();

	void ParsedInstruction(Instruction::opcode opcode);
	void InstructionRef(Cache::checkRet L1Hit,
						Cache::eviction L1Evict,
						Cache::checkRet L2Hit,
						Cache::eviction L2Evict);

	void L1DEvict(Cache::eviction L1DEvict);
	void L2Evict(Cache::eviction L2Evict);
	void L1DRef(Cache::checkRet L1DHit);
	void L2Ref(Cache::checkRet L2Hit);
	void AddExecInfoTime(uint32 execTime);
	uint64 GetExecTime();
	void AddCycleCount(Instruction::opcode opcode,uint64 cycle);

private:
	uint64 m_numTotal;
	uint64 m_numLoad;
	uint64 m_numBranch;
	uint64 m_numStore;
	uint64 m_numComp;

	uint64 m_cycleTotal;
	uint64 m_cycleLoad;
	uint64 m_cycleBranch;
	uint64 m_cycleStore;
	uint64 m_cycleComp;

	uint64 m_execTime;

	uint64 m_instRefs;
	uint64 m_dataRefs;

	uint64 m_hitCount[Cache::CL_NUMLEVELS];
	uint64 m_missCount[Cache::CL_NUMLEVELS];
	uint64 m_accessTotal[Cache::CL_NUMLEVELS];
	uint64 m_kickouts[Cache::CL_NUMLEVELS];
	uint64 m_dirtyKickouts[Cache::CL_NUMLEVELS];
	uint64 m_transfers[Cache::CL_NUMLEVELS];
};



#endif /* RESULTS_H_ */
