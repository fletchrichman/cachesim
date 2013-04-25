//Calculate costs and other results, write everything to output file
#include "results.h"
#include "config.h"
#include <stdio.h>
#include <iostream>

using namespace std;
bool printBool=false;
Results::Results()
		: m_numTotal(0), m_numLoad(0), m_numBranch(0), m_numStore(0), m_numComp(0), m_cycleTotal(0), m_cycleLoad(0), m_cycleBranch(0), m_cycleStore(0), m_cycleComp(0), m_execTime(0), m_instRefs(0), m_dataRefs(0){
	for(int ii=0;ii<Cache::CL_NUMLEVELS;ii++){
		m_transfers[ii]=0;
		m_accessTotal[ii]=0;
		m_hitCount[ii]=0;
		m_missCount[ii]=0;
		m_kickouts[ii]=0;
		m_dirtyKickouts[ii]=0;  
	}
}

void Results::PrintResults(){
	printf("                         Simulation Results                               \n");
	printf("--------------------------------------------------------------------------\n");

	//Memory Config
	printf("Memory system:\n");
	printf("   Dcache size = %u : ways = %u : block size = %u\n", L1_cache_size, L1_assoc, L1_block_size);
	printf("   Icache size = %u : ways = %u : block size = %u\n", L1_cache_size, L1_assoc, L1_block_size);
	printf("   L2-cache size = %u : ways = %u : block size = %u\n", L2_cache_size, L2_assoc, L2_block_size);
	printf("   Memory ready time = %u : chunksize = %u : chunktime = %u\n\n", mem_ready, mem_chunksize, mem_chunktime);

	//Execution Time and References
	printf("Execute time = %llu     Total Refs = %llu\n",m_execTime,(m_dataRefs+m_instRefs));
	printf("Instruction Refs = %llu     Data Refs = %llu\n",m_instRefs,m_dataRefs);
	printf("\n");

	//Number of Instructions and Percentages
	printf("Number of Instructions:     [Percentage]\n");
	printf("   Loads (L) = %llu    [%2.2f%%]   :   Stores (S) = %llu    [%2.2f%%]\n",m_numLoad,(float)(m_numLoad*100.0/(float)m_numTotal),m_numStore,(float)(m_numStore*100.0/(float)m_numTotal));
	printf("   Branch (B) = %llu    [%2.2f%%]   :   Computation (C) = %llu    [%2.2f%%]\n",m_numBranch,(m_numBranch*100.0/(float)m_numTotal),m_numComp,(m_numComp*100.0/(float)m_numTotal));
	printf("   Total = %llu\n",m_numTotal);
	printf("\n");

	//Cycles Time and Referencess Info
	printf("Cycles for Instructions:     [Percentage]\n");
	printf("   Loads (L) = %llu    [%2.2f%%]   :   Stores (S) = %llu    [%2.2f%%]\n",m_cycleLoad,(float)(m_cycleLoad*100.0/(float)m_cycleTotal),m_cycleStore,(float)(m_cycleStore*100.0/(float)m_cycleTotal));
	printf("   Branch (B) = %llu    [%2.2f%%]   :   Computation (C) = %llu    [%2.2f%%]\n",m_cycleBranch,(m_cycleBranch*100.0/(float)m_cycleTotal),m_cycleComp,(m_cycleComp*100.0/(float)m_cycleTotal));
	printf("   Total = %llu\n",m_cycleTotal);
	printf("\n");

	//Instruction types & CPI
	printf("Cycles per Instruction (CPI):\n");
	printf("   Loads (L) = %2.2f      :   Stores (S) = %2.2f\n",(float)(m_cycleLoad / (float)m_numLoad),(float)(m_cycleStore / (float)m_numStore));
	printf("   Branch (B) = %2.2f     :   Computation (C) = %2.2f\n",(float)(m_cycleBranch / (float)m_numBranch),(float)(m_cycleComp / (float)m_numComp));
	printf("   Overall = %2.2f\n",(float)(m_cycleTotal/ (float)m_numTotal));
	printf("\n");

	//Ideal vs Simulated
	printf("Cycles for processor w/perfect memory system %llu\n",2*m_instRefs);
	printf("Cycles for processor w/simulated memory system %llu\n",m_execTime);
	printf("Ratio of simulated/perfect performance %f\n",(float)(m_execTime/(float)(2*m_instRefs)));
	printf("\n");

	//L1I
	printf("Memory Level:   L1I\n");
	printf("   Hit Count = %llu     Miss Count = %llu   Total Request = %llu\n",m_hitCount[Cache::CL_L1I],m_missCount[Cache::CL_L1I],m_accessTotal[Cache::CL_L1I]);
	printf("   Hit Rate = %2.2f%%    Miss Rate = %2.2f%%\n",(float)(m_hitCount[Cache::CL_L1I]*100/(float)m_accessTotal[Cache::CL_L1I]),(float)(m_missCount[Cache::CL_L1I]*100/(float)m_accessTotal[Cache::CL_L1I]));
	printf("   Kickouts : %llu   Dirty Kickouts : %llu  Transfers : %llu\n",m_kickouts[Cache::CL_L1I],m_dirtyKickouts[Cache::CL_L1I],m_transfers[Cache::CL_L1I]);
	printf("\n");

	//L1D
	printf("Memory Level:   L1D\n");
	printf("   Hit Count = %llu     Miss Count = %llu   Total Request = %llu\n",m_hitCount[Cache::CL_L1D],m_missCount[Cache::CL_L1D],m_accessTotal[Cache::CL_L1D]);
	printf("   Hit Rate = %2.2f%%    Miss Rate = %2.2f%%\n",(float)(m_hitCount[Cache::CL_L1D]*100/(float)m_accessTotal[Cache::CL_L1D]),(float)(m_missCount[Cache::CL_L1D]*100/(float)m_accessTotal[Cache::CL_L1D]));
	printf("   Kickouts : %llu   Dirty Kickouts : %llu  Transfers : %llu\n",m_kickouts[Cache::CL_L1D],m_dirtyKickouts[Cache::CL_L1D],m_transfers[Cache::CL_L1D]);
	printf("\n");

	//L2
	printf("Memory Level:   L2\n");
	printf("   Hit Count = %llu     Miss Count = %llu   Total Request = %llu\n",m_hitCount[Cache::CL_L2],m_missCount[Cache::CL_L2],m_accessTotal[Cache::CL_L2]);
	printf("   Hit Rate = %2.2f%%    Miss Rate = %2.2f%%\n",(float)(m_hitCount[Cache::CL_L2]*100/(float)m_accessTotal[Cache::CL_L2]),(float)(m_missCount[Cache::CL_L2]*100/(float)m_accessTotal[Cache::CL_L2]));
	printf("   Kickouts : %llu   Dirty Kickouts : %llu  Transfers : %llu\n",m_kickouts[Cache::CL_L2],m_dirtyKickouts[Cache::CL_L2],m_transfers[Cache::CL_L2]);
	printf("\n");
}

//Keep track of number of each type of instruction processed
void Results::ParsedInstruction(Instruction::opcode opcode){
	m_numTotal++;
	m_instRefs++;
	switch(opcode){
		case Instruction::O_Load:
			m_numLoad++;
			m_dataRefs++;
			break;
		case Instruction::O_Store:
			m_numStore++;
			m_dataRefs++;
			break;
		case Instruction::O_Branch:
			m_numBranch++;
			break;
		case Instruction::O_Computation:
			m_numComp++;
			break;
		default:
			break;
	}
}

//Keep track of number of operations
void Results::AddCycleCount(Instruction::opcode opcode,uint64 cycle){
	m_cycleTotal+=cycle;
	switch(opcode){
		case Instruction::O_Load:
			m_cycleLoad+=cycle;
			break;
		case Instruction::O_Store:
			m_cycleStore+=cycle;
			break;
		case Instruction::O_Branch:
			m_cycleBranch+=cycle;
			break;
		case Instruction::O_Computation:
			m_cycleComp+=cycle;
			break;
		default:
			break;
	}
}

void Results::InstructionRef(Cache::checkRet L1Hit,Cache::eviction L1Evict,Cache::checkRet L2Hit,Cache::eviction L2Evict){
	m_accessTotal[Cache::CL_L1I]++;
	if (L1Hit == Cache::CR_HIT){ 			//L1I hit
		m_execTime += L1_hit_time;			//Add L1I hit time
		m_hitCount[Cache::CL_L1I]++;		//Increment L1I hit count
	}
	else if (L1Hit == Cache::CR_MISS){		//L1I miss
		m_execTime += L1_miss_time;			//Add L1I miss time
		m_missCount[Cache::CL_L1I]++;		//Increment L1I miss count
		m_transfers[Cache::CL_L1I]++;		//Increment L1I transgers
		if (L1Evict == Cache::E_CLEAN) m_kickouts[Cache::CL_L1I]++; //Increment L1I kickouts
		m_accessTotal[Cache::CL_L2]++;		//Increment Total Access
		
		if (L2Hit == Cache::CR_HIT){		//L2 hit
			m_execTime += L2_hit_time;		//Add L2 hit time
											//Transfer time L2 to L1
			m_execTime += (L1_block_size / L2_bus_width) * L2_transfer_time;	
			m_execTime += L1_hit_time;		//Add L1I hit time
			m_hitCount[Cache::CL_L2]++;		//Increment L2 hit count
		}
		else if (L2Hit == Cache::CR_MISS){	//L2 miss
			m_execTime += L2_miss_time;		//Add L2 miss time

											//Transfer Time L2-->Memory
			m_execTime += (mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime));
			m_execTime += L2_hit_time;		//Add L2 hit time

											//Transfer from l2 to l1
			m_execTime += ((L1_block_size / L2_bus_width) * L2_transfer_time);
			m_execTime += L1_hit_time;		//Add L1i hit time
			m_missCount[Cache::CL_L2]++;	//Increment miss counts
			m_transfers[Cache::CL_L2]++;	//Increment transfers

			if (L2Evict == Cache::E_CLEAN) m_kickouts[Cache::CL_L2]++;
			else if (L2Evict == Cache::E_DIRTY){
				m_kickouts[Cache::CL_L2]++;
				m_dirtyKickouts[Cache::CL_L2]++;
				m_execTime += (mem_sendaddr + mem_ready + ((L2_block_size / mem_chunksize) * mem_chunktime));
			}
		}
	}
}

//Handle L1D Eviction Results
void Results::L1DEvict(Cache::eviction L1DEvict){
	if (L1DEvict == Cache::E_CLEAN) m_kickouts[Cache::CL_L1D]++;
	else if (L1DEvict == Cache::E_DIRTY){
		m_kickouts[Cache::CL_L1D]++;
		m_dirtyKickouts[Cache::CL_L1D]++;
		m_execTime += (L1_block_size / L2_bus_width) * L2_transfer_time;

	}
}

//Handle L2 Eviction Results
void Results::L2Evict(Cache::eviction L2Evict){
	if (L2Evict == Cache::E_CLEAN) m_kickouts[Cache::CL_L2]++;
	else if (L2Evict == Cache::E_DIRTY){
		m_kickouts[Cache::CL_L2]++;
		m_dirtyKickouts[Cache::CL_L2]++;
		m_execTime += mem_sendaddr + mem_ready + ((L2_block_size / mem_chunksize) * mem_chunktime);
	}
}

//Handle LD1 Results
void Results::L1DRef(Cache::checkRet L1DHit){
	m_accessTotal[Cache::CL_L1D]++;
	if (L1DHit == Cache::CR_HIT){
		m_execTime += L1_hit_time;
		m_hitCount[Cache::CL_L1D]++;
	}
	else {
		m_execTime += L1_miss_time;
		m_execTime += (L1_block_size / L2_bus_width) * L2_transfer_time;
		m_execTime += L1_hit_time;
		m_missCount[Cache::CL_L1D]++;
		m_transfers[Cache::CL_L1D]++;
	}
}

//Handle L2 Results
void Results::L2Ref(Cache::checkRet L2Hit){
	m_accessTotal[Cache::CL_L2]++;
	if (L2Hit == Cache::CR_HIT){	//Add L2 hit time
		m_execTime += L2_hit_time;
		m_hitCount[Cache::CL_L2]++;
	}
	else {
		m_execTime += L2_miss_time;
		m_execTime += mem_sendaddr + mem_ready + ((L2_block_size / mem_chunksize) * mem_chunktime);
		m_execTime += L2_hit_time;		//Add L2 hit time
		m_missCount[Cache::CL_L2]++;
		m_transfers[Cache::CL_L2]++;
	}
}

//Increment Execution Info
void Results::AddExecInfoTime(uint32 execTime){
	m_execTime += execTime;
}

//Get Execution Info
uint64 Results::GetExecTime(){
	return m_execTime;
}