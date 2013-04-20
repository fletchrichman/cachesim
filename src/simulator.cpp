//Main simulator
#include <iostream>
#include "simulator.h"

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
void Simulator::HandleInstruction(Instruction* instr, Cache* L1I, Cache* L1D, Cache* L2, Results* results){
	//INSTRUCTION FETCH============================================================================================
	uint32 pc = instr->GetPc();								//Get inst
	Cache::checkRet instrHitL1 = L1I->checkInCache(pc);		//Look for inst in L1
	Cache::checkRet instrHitL2;
	Cache::eviction instrEvictL1;
	Cache::eviction instrEvictL2;

	if (instrHitL1 == Cache::CR_MISS){					    //L1 miss
		instrEvictL1 = L1I->checkAddRequiresEviction(pc);   //Check if we need to evict L1
		instrHitL2 = L2->checkInCache(pc); 				    //Inst. not in L1, look for it in L2

		if (instrHitL2 == Cache::CR_MISS){				    //L2 miss
			instrEvictL2 = L2->checkAddRequiresEviction(pc);//Check if we need to evict L2
			L2->addToCache(pc);
		}
		else PRINTACTION(endl << "L2 Hit");					//L2 hit
		L1I->addToCache(pc);								//Add inst to L1 Instruction cache
	}
	else PRINTACTION(endl << "L1I Hit");					//L1I hit
	results->InstructionRef(instrHitL1, instrEvictL1, instrHitL2, instrEvictL2);
	//END INSTRUCTION FETCH========================================================================================

	switch(instr->GetOpcode()){
		case Instruction::O_Load:
		case Instruction::O_Store:
		{
			//BEGIN DATA FETCH=====================================================================================
			uint32 addr = instr->GetExecInfo();									  //Get inst
			Cache::checkRet dataHitL1 = L1D->checkInCache(addr);    			  //Look for inst in L1
			Cache::checkRet dataHitL2;
			Cache::eviction dataEvictL1;
			Cache::eviction dataEvictL2;
			Cache::checkRet dataWriteBackHitL2;

			if (dataHitL1 == Cache::CR_MISS){									  //L1D miss
				dataEvictL1 = L1D->checkAddRequiresEviction(addr);  			  //Check if we need to evict L1
				if (dataEvictL1 == Cache::E_DIRTY){								  //Check dirty evict L1
					uint32 evictAddrL1 = L1D->getAddressToEvict(addr); 			  //Get eviction address
					dataWriteBackHitL2 = L2->checkInCache(evictAddrL1);			  //Write back to L2
					//If evicted address from L1 is found in L2, potentially write to it
					if (dataWriteBackHitL2 == Cache::CR_HIT) L2->write(evictAddrL1);
				
					else { 														  //It is not in L2
						dataEvictL2 = L2->checkAddRequiresEviction(evictAddrL1);  //Check if we need to evict from L2
						if (dataEvictL2 != Cache::E_NOEVICT){					  
							results->L2Evict(dataEvictL2);						  //Evict L2
							if (dataEvictL2 != Cache::E_DIRTY) PRINTACTION(endl << "Dirty writeback from L2");
						}
						L2->addToCache(evictAddrL1);							  //Add to L2 cache
						L2->write(evictAddrL1);									  //Write L1 evicted to L2
					}

					results->L2Ref(dataWriteBackHitL2);							  //Write to results vector that   
					results->L1DEvict(dataEvictL1);								  //there was a dirty writeback from L1D
				}
				else if (dataEvictL1 == Cache::E_CLEAN) results->L1DEvict(dataEvictL1);

				dataHitL2 = L2->checkInCache(addr);								  //Inst. was not in L1, look for it in L2
				if (dataHitL2 == Cache::CR_MISS){								  //L2 miss
					dataEvictL2 = L2->checkAddRequiresEviction(addr);			  //Check if we need to evict L2
					if (dataEvictL2 != Cache::E_NOEVICT) results->L2Evict(dataEvictL2);//Evict L2
					L2->addToCache(addr);										  //Write new address to L2
				}	
				else PRINTACTION(endl << "L2 Hit");								  //L2 hit
				
				results->L2Ref(dataHitL2);										  //Write to results vector
				L1D->addToCache(addr);											  //Add address to L1D
			}
			else PRINTACTION(endl << "L1D Hit");								  //L1D hit

			if (instr->GetOpcode() == Instruction::O_Store) L1D->write(addr);	  //If inst is a store, write address to L1D
			results->L1DRef(dataHitL1);											  //Write to results vector
			break;
		}
		//END DATA FETCH===========================================================================================

		case Instruction::O_Branch:
		case Instruction::O_Computation:
		{
			PRINT("Add exec time (+%d)\n",1);
			results->AddExecInfoTime(instr->GetExecInfo());						  //Add execution time to results
			break;
		}
		default:
			break;

	}
}



