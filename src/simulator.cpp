/*
 * simulator.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#include "simulator.h"

#include <iostream>

#undef DEBUG
#ifdef DEBUG
#define PRINTACTION(output) (cout << output)
#else
#define PRINTACTION(output)
#endif
//#define CPRINT
#ifdef CPRINT
#define PRINT(format,...) printf(format,##__VA_ARGS__)
#else
#define PRINT(format,...)
#endif


using namespace std;

void Simulator::HandleInstruction(Instruction* instr,
								  Cache* L1I,
								  Cache* L1D,
								  Cache* L2,
								  Results* results)
{
	// =======================
	// BEGIN INSTRUCTION FETCH
	// =======================

	uint32 pc = instr->GetPc();

	// Look for instruction in L1 cache
	Cache::checkRet instrHitL1 = L1I->checkInCache(pc);

	Cache::checkRet instrHitL2;
	Cache::eviction instrEvictL1;
	Cache::eviction instrEvictL2;

	if (instrHitL1 == Cache::CR_MISS)
	{
		PRINTACTION(endl << "L1I Miss");

		// See whether we will have to evict from L1
		instrEvictL1 = L1I->checkAddRequiresEviction(pc);

		// If dirty evict, need to write it back
		/*if (instrEvictL1 == Cache::E_DIRTY)
		{
			// This will never happen in the instruction cache
		}*/

		// Instruction not in L1 cache, look in L2
		instrHitL2 = L2->checkInCache(pc);

		if (instrHitL2 == Cache::CR_MISS)
		{
			PRINTACTION(endl << "L2 Miss");

			// See whether we will have to evict from L2
			instrEvictL2 = L2->checkAddRequiresEviction(pc);

			L2->addToCache(pc);
		}
		else
		{
			PRINTACTION(endl << "L2 Hit");
		}

		L1I->addToCache(pc);
	}
	else
	{
		PRINTACTION(endl << "L1I Hit");
	}

	results->InstructionRef(instrHitL1, instrEvictL1, instrHitL2, instrEvictL2);

	// =====================
	// END INSTRUCTION FETCH
	// =====================


	switch(instr->GetOpcode())
	{
		case Instruction::O_Load:
		case Instruction::O_Store:
		{
			PRINTACTION(endl << "-------");

			// =====================
			// BEGIN DATA FETCH
			// =====================

			uint32 addr = instr->GetExecInfo();

			// Look for instruction in L1 cache
			Cache::checkRet dataHitL1 = L1D->checkInCache(addr);

			Cache::checkRet dataHitL2;
			Cache::eviction dataEvictL1;
			Cache::eviction dataEvictL2;
			Cache::checkRet dataWriteBackHitL2;

			if (dataHitL1 == Cache::CR_MISS)
			{
				PRINTACTION(endl << "L1D Miss");

				// See whether we will have to evict from L1
				dataEvictL1 = L1D->checkAddRequiresEviction(addr);

				// If dirty evict, need to write it back
				if (dataEvictL1 == Cache::E_DIRTY)
				{
					uint32 evictAddrL1 = L1D->getAddressToEvict(addr);

					dataWriteBackHitL2 = L2->checkInCache(evictAddrL1);

					// If addr evicted from L1 is found in L2, just need to potentially write to it
					if (dataWriteBackHitL2 == Cache::CR_HIT)
					{
						L2->write(evictAddrL1);
					}
					// If it wasn't in L2, need to handle that
					else
					{
						// Check if we also need to evict from L2
						dataEvictL2 = L2->checkAddRequiresEviction(evictAddrL1);

						if (dataEvictL2 != Cache::E_NOEVICT)
						{
							results->L2Evict(dataEvictL2);

							if (dataEvictL2 != Cache::E_DIRTY)
							{
								PRINTACTION(endl << "Dirty writeback from L2");
							}
						}

						// Need to add it to L2 cache, then we can write
						L2->addToCache(evictAddrL1);
						L2->write(evictAddrL1);
					}

					results->L2Ref(dataWriteBackHitL2);

					PRINTACTION(endl << "Dirty writeback from L1D");
					results->L1DEvict(dataEvictL1);
				}
				else if (dataEvictL1 == Cache::E_CLEAN)
				{
					results->L1DEvict(dataEvictL1);
				}

				// Instruction not in L1 cache, look in L2
				dataHitL2 = L2->checkInCache(addr);

				if (dataHitL2 == Cache::CR_MISS)
				{
					PRINTACTION(endl << "L2 Miss");

					// See whether we will have to evict from L2
					dataEvictL2 = L2->checkAddRequiresEviction(addr);

					if (dataEvictL2 != Cache::E_NOEVICT)
					{
						results->L2Evict(dataEvictL2);
					}

					L2->addToCache(addr);
				}
				else
				{
					PRINTACTION(endl << "L2 Hit");
				}

				results->L2Ref(dataHitL2);

				L1D->addToCache(addr);
			}
			else
			{
				PRINTACTION(endl << "L1D Hit");
			}

			if (instr->GetOpcode() == Instruction::O_Store)
			{
				L1D->write(addr);
			}

			results->L1DRef(dataHitL1);

			break;
		}
		// =====================
		// END DATA FETCH
		// =====================
		case Instruction::O_Branch:
		case Instruction::O_Computation:
		{
			PRINT("Add exec time (+%d)\n",1);
			results->AddExecInfoTime(instr->GetExecInfo());
			break;
		}
		default:
			break;

	}
	PRINTACTION(endl << "------------------------------------------------------");
}



