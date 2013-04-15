/*
 * results.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#include "results.h"

#include <iostream>
#include <stdio.h>

#include "config.h"
#define CPRINT
#ifdef CPRINT
#define PRINT(format,...) if(printBool) printf(format,##__VA_ARGS__)
#else
#define PRINT(format,...)
#endif
using namespace std;
bool printBool=false;
Results::Results()
		: m_numTotal(0), m_numLoad(0), m_numBranch(0), m_numStore(0), m_numComp(0),
		  m_cycleTotal(0), m_cycleLoad(0), m_cycleBranch(0), m_cycleStore(0), m_cycleComp(0),
		  m_execTime(0),
		  m_instRefs(0), m_dataRefs(0)
{
	// Empty on purpose
	for(int ii=0;ii<Cache::CL_NUMLEVELS;ii++)
	{
		  m_hitCount[ii]=0;
		  m_missCount[ii]=0;
		  m_accessTotal[ii]=0;
		  m_kickouts[ii]=0;
		  m_dirtyKickouts[ii]=0;
		  m_transfers[ii]=0;
	}
}

void Results::PrintResults()
{
	printf("--------------------------------------------------------------------------\n");
	printf("                         Simulation Results                               \n");
	printf("--------------------------------------------------------------------------\n");

	/*Print out Memory System Configuration*/
	printf("Memory system:\n");
	printf("   Dcache size = %u : ways = %u : block size = %u\n", L1_cache_size, L1_assoc, L1_block_size);
	printf("   Icache size = %u : ways = %u : block size = %u\n", L1_cache_size, L1_assoc, L1_block_size);
	printf("   L2-cache size = %u : ways = %u : block size = %u\n", L2_cache_size, L2_assoc, L2_block_size);
	printf("   Memory ready time = %u : chunksize = %u : chunktime = %u\n\n", mem_ready, mem_chunksize, mem_chunktime);

	/*Print out Exec time and Refs information*/
	printf("Execute time = %llu     Total Refs = %llu\n",
					m_execTime,
					(m_dataRefs+m_instRefs));
	printf("Instruction Refs = %llu     Data Refs = %llu\n",
							m_instRefs,
							m_dataRefs);

	printf("\n");

	/*Print out Number of Instructions and Percentage*/
	printf("Number of Instructions:     [Percentage]\n");
	printf("   Loads (L) = %llu    [%2.2f%%]   :   Stores (S) = %llu    [%2.2f%%]\n",
					m_numLoad,
					(float)(m_numLoad*100.0/(float)m_numTotal),
					m_numStore,
					(float)(m_numStore*100.0/(float)m_numTotal));
	printf("   Branch (B) = %llu    [%2.2f%%]   :   Computation (C) = %llu    [%2.2f%%]\n",
							m_numBranch,
							(m_numBranch*100.0/(float)m_numTotal),
							m_numComp,
							(m_numComp*100.0/(float)m_numTotal));
	printf("   Total = %llu\n",m_numTotal);

	printf("\n");

	/*Print out Cycles time and Refs information*/
	printf("Cycles for Instructions:     [Percentage]\n");
	printf("   Loads (L) = %llu    [%2.2f%%]   :   Stores (S) = %llu    [%2.2f%%]\n",
					m_cycleLoad,
					(float)(m_cycleLoad*100.0/(float)m_cycleTotal),
					m_cycleStore,
					(float)(m_cycleStore*100.0/(float)m_cycleTotal));
	printf("   Branch (B) = %llu    [%2.2f%%]   :   Computation (C) = %llu    [%2.2f%%]\n",
							m_cycleBranch,
							(m_cycleBranch*100.0/(float)m_cycleTotal),
							m_cycleComp,
							(m_cycleComp*100.0/(float)m_cycleTotal));
	printf("   Total = %llu\n",m_cycleTotal);

	printf("\n");

	/*Print out CPI information*/
	printf("Cycles per Instruction (CPI):\n");
	printf("   Loads (L) = %2.2f      :   Stores (S) = %2.2f\n",
					(float)(m_cycleLoad / (float)m_numLoad),
					(float)(m_cycleStore / (float)m_numStore));
	printf("   Branch (B) = %2.2f     :   Computation (C) = %2.2f\n",
			(float)(m_cycleBranch / (float)m_numBranch),
			(float)(m_cycleComp / (float)m_numComp));
	printf("   Overall = %2.2f\n",(float)(m_cycleTotal/ (float)m_numTotal));

	printf("\n");

	/*Print out Ideal Vs  Simulated*/
	printf("Cycles for processor w/perfect memory system %llu\n",2*m_instRefs);
	printf("Cycles for processor w/simulated memory system %llu\n",m_execTime);
	printf("Ratio of simulated/perfect performance %f\n",(float)(m_execTime/(float)(2*m_instRefs)));

	printf("\n");

	/*Print out memory level L1I*/
	printf("Memory Level:   L1I\n");
	printf("   Hit Count = %llu     Miss Count = %llu   Total Request = %llu\n",
			m_hitCount[Cache::CL_L1I],
			m_missCount[Cache::CL_L1I],
			m_accessTotal[Cache::CL_L1I]);
	printf("   Hit Rate = %2.2f%%    Miss Rate = %2.2f%%\n",
			(float)(m_hitCount[Cache::CL_L1I]*100/(float)m_accessTotal[Cache::CL_L1I]),
			(float)(m_missCount[Cache::CL_L1I]*100/(float)m_accessTotal[Cache::CL_L1I]));
	printf("   Kickouts : %llu   Dirty Kickouts : %llu  Transfers : %llu\n",
			m_kickouts[Cache::CL_L1I],
			m_dirtyKickouts[Cache::CL_L1I],
			m_transfers[Cache::CL_L1I]);

	printf("\n");

	/*Print out memory level L1D*/
	printf("Memory Level:   L1D\n");
	printf("   Hit Count = %llu     Miss Count = %llu   Total Request = %llu\n",
			m_hitCount[Cache::CL_L1D],
			m_missCount[Cache::CL_L1D],
			m_accessTotal[Cache::CL_L1D]);
	printf("   Hit Rate = %2.2f%%    Miss Rate = %2.2f%%\n",
			(float)(m_hitCount[Cache::CL_L1D]*100/(float)m_accessTotal[Cache::CL_L1D]),
			(float)(m_missCount[Cache::CL_L1D]*100/(float)m_accessTotal[Cache::CL_L1D]));
	printf("   Kickouts : %llu   Dirty Kickouts : %llu  Transfers : %llu\n",
			m_kickouts[Cache::CL_L1D],
			m_dirtyKickouts[Cache::CL_L1D],
			m_transfers[Cache::CL_L1D]);

	printf("\n");

	/*Print out memory level L2*/
	printf("Memory Level:   L2\n");
	printf("   Hit Count = %llu     Miss Count = %llu   Total Request = %llu\n",
			m_hitCount[Cache::CL_L2],
			m_missCount[Cache::CL_L2],
			m_accessTotal[Cache::CL_L2]);
	printf("   Hit Rate = %2.2f%%    Miss Rate = %2.2f%%\n",
			(float)(m_hitCount[Cache::CL_L2]*100/(float)m_accessTotal[Cache::CL_L2]),
			(float)(m_missCount[Cache::CL_L2]*100/(float)m_accessTotal[Cache::CL_L2]));
	printf("   Kickouts : %llu   Dirty Kickouts : %llu  Transfers : %llu\n",
			m_kickouts[Cache::CL_L2],
			m_dirtyKickouts[Cache::CL_L2],
			m_transfers[Cache::CL_L2]);

	printf("\n");

/*Print Cache Cost Information*/
	uint32 numAssocDoubles=0;
	uint64 L1Cost=0;
	uint64 L2Cost=0;
	uint64 totalCost=0;

	/*Calculate L1 Cost*/
	while(L1_assoc>>=1) numAssocDoubles++;
	L1Cost=(L1_cache_size/(4*1024))*(100+(100*numAssocDoubles));
	totalCost+=2*L1Cost;

	/*Calculate L2 Cost*/
	numAssocDoubles=0;
	while(L2_assoc>>=1) numAssocDoubles++;
	L2Cost=(L2_cache_size/(64*1024))*(50+(50*numAssocDoubles));
	totalCost+=L2Cost;

	/*Calculate memory cost*/
	uint32 latencyDouble=0;
	uint32 bandwidthDouble=0;
	uint64 temp;
	uint64 memCost=0;
	temp=100/mem_ready;
	while(temp>>=1) latencyDouble++;
	temp=mem_chunksize/16;
	while(temp>>=1) bandwidthDouble++;
	memCost=latencyDouble*200+bandwidthDouble*100+75;
	totalCost+=memCost;

	printf("L1 cache cost (Icache $%llu) + (Dcache $%llu) = $%llu\n",L1Cost,L1Cost,2*L1Cost);
	printf("L2 cache cost = $%llu\n",L2Cost);
	printf("Memory cost = $%llu\n",memCost);
	printf("Total cost = $%llu\n",totalCost);

/*
	// L1I Cache Summary
	cout << endl << endl
		 << "Memory Level: L1I" << endl
		 << "\tHit Count = " << m_hitCount[Cache::CL_L1I]
		 << "\tMiss Count = " << m_missCount[Cache::CL_L1I]
	     << "\tTotal Request = " << m_accessTotal[Cache::CL_L1I] << endl;
	cout.setf(std::ios::fixed);
	cout.precision(1);
	double hitrate = 100 * (double) m_hitCount[Cache::CL_L1I] / (double) m_accessTotal[Cache::CL_L1I];
	double missrate = 100 * (double) m_missCount[Cache::CL_L1I] / (double) m_accessTotal[Cache::CL_L1I];
	cout << "\tHit Rate = " << hitrate << "%"
		 << "\tMiss Rate = " << missrate << "%" << endl
		 << "\tKickouts = " << m_kickouts[Cache::CL_L1I]
		 << "\tDirty Kickouts = " << m_dirtyKickouts[Cache::CL_L1I]
		 << "\tTransfers = " << m_transfers[Cache::CL_L1I];

	// L1D Cache Summary
	cout << endl << endl
		 << "Memory Level: L1D" << endl
		 << "\tHit Count = " << m_hitCount[Cache::CL_L1D]
		 << "\tMiss Count = " << m_missCount[Cache::CL_L1D]
		 << "\tTotal Request = " << m_accessTotal[Cache::CL_L1D] << endl;
	cout.setf(std::ios::fixed);
	cout.precision(1);
	hitrate = 100 * (double) m_hitCount[Cache::CL_L1D] / (double) m_accessTotal[Cache::CL_L1D];
	missrate = 100 * (double) m_missCount[Cache::CL_L1D] / (double) m_accessTotal[Cache::CL_L1D];
	cout << "\tHit Rate = " << hitrate << "%"
		 << "\tMiss Rate = " << missrate << "%" << endl
		 << "\tKickouts = " << m_kickouts[Cache::CL_L1D]
		 << "\tDirty Kickouts = " << m_dirtyKickouts[Cache::CL_L1D]
		 << "\tTransfers = " << m_transfers[Cache::CL_L1D];

	// L2 Cache Summary
	cout << endl << endl
		 << "Memory Level: L2" << endl
		 << "\tHit Count = " << m_hitCount[Cache::CL_L2]
		 << "\tMiss Count = " << m_missCount[Cache::CL_L2]
		 << "\tTotal Request = " << m_accessTotal[Cache::CL_L2] << endl;
	cout.setf(std::ios::fixed);
	cout.precision(1);
	hitrate = 100 * (double) m_hitCount[Cache::CL_L2] / (double) m_accessTotal[Cache::CL_L2];
	missrate = 100 * (double) m_missCount[Cache::CL_L2] / (double) m_accessTotal[Cache::CL_L2];
	cout << "\tHit Rate = " << hitrate << "%"
		 << "\tMiss Rate = " << missrate << "%" << endl
		 << "\tKickouts = " << m_kickouts[Cache::CL_L2]
		 << "\tDirty Kickouts = " << m_dirtyKickouts[Cache::CL_L2]
		 << "\tTransfers = " << m_transfers[Cache::CL_L2];
	*/

}

void Results::ParsedInstruction(Instruction::opcode opcode)
{
	m_numTotal++;
	m_instRefs++;

	switch(opcode)
	{
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

void Results::AddCycleCount(Instruction::opcode opcode,uint64 cycle)
{
	m_cycleTotal+=cycle;

	switch(opcode)
	{
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

void Results::InstructionRef(Cache::checkRet L1Hit,
							 Cache::eviction L1Evict,
						 	 Cache::checkRet L2Hit,
						     Cache::eviction L2Evict)
{
	m_accessTotal[Cache::CL_L1I]++;

	if (L1Hit == Cache::CR_HIT)
	{
		PRINT("Add L1i hit time (+%d)\n",L1_hit_time);
		m_execTime += L1_hit_time;
		m_hitCount[Cache::CL_L1I]++;
	}
	else if (L1Hit == Cache::CR_MISS)
	{
		PRINT("Add L1i miss time (+%d)\n",L1_miss_time);
		m_execTime += L1_miss_time;

		m_missCount[Cache::CL_L1I]++;
		m_transfers[Cache::CL_L1I]++;

		if (L1Evict == Cache::E_CLEAN)
		{
			m_kickouts[Cache::CL_L1I]++;
		}

		m_accessTotal[Cache::CL_L2]++;

		if (L2Hit == Cache::CR_HIT)
		{
			PRINT("Add L2 hit time (+%d)\n",L2_hit_time);
			m_execTime += L2_hit_time;

			// Time for xfer from L2 to L1
			PRINT("Bringing line into L1i.\n");
			PRINT("Add L2 to L1 transfer time (+%d)\n",((L1_block_size / L2_bus_width) * L2_transfer_time));
			m_execTime += (L1_block_size / L2_bus_width) * L2_transfer_time;

			//Replay of L1
			PRINT("Add L1i hit replay time (+%d)\n",L1_hit_time);
			m_execTime += L1_hit_time;

			m_hitCount[Cache::CL_L2]++;
		}
		else if (L2Hit == Cache::CR_MISS)
		{
			//L2 Miss time
			PRINT("Add L2 miss time (+%d)\n",L2_miss_time);
			m_execTime += L2_miss_time;

			// Time for xfer from main mem to L2
			PRINT("Bringing line into L2.\n");
			PRINT("Add memory to L2 transfer time (+%d)\n",(mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime)));
			m_execTime += (mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime));

			/*Replay time*/
			PRINT("Add L2 hit replay time (+%d)\n",L2_hit_time);
			m_execTime += L2_hit_time;

			//Transfer from l2 to l1
			PRINT("Bringing line into L1i.\n");
			PRINT("Add L2 to L1 transfer time (+%d)\n",((L1_block_size / L2_bus_width) * L2_transfer_time));
			m_execTime += ((L1_block_size / L2_bus_width) * L2_transfer_time);

			/*Replay time*/
			PRINT("Add L1i hit replay time (+%d)\n",L1_hit_time);
			m_execTime += L1_hit_time;

			m_missCount[Cache::CL_L2]++;
			m_transfers[Cache::CL_L2]++;

			if (L2Evict == Cache::E_CLEAN)
			{
				m_kickouts[Cache::CL_L2]++;
			}
			else if (L2Evict == Cache::E_DIRTY)
			{
				m_kickouts[Cache::CL_L2]++;
				m_dirtyKickouts[Cache::CL_L2]++;

				// Time for xfer from main L2 to main mem
				PRINT("Bringing line into L2.\n");
				PRINT("Add memory to L2 transfer time (+%d)\n",(mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime)));
				m_execTime += (mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime));
			}
		}
	}
}

void Results::L1DEvict(Cache::eviction L1DEvict)
{
	if (L1DEvict == Cache::E_CLEAN)
	{
		m_kickouts[Cache::CL_L1D]++;
	}
	else if (L1DEvict == Cache::E_DIRTY)
	{
		m_kickouts[Cache::CL_L1D]++;
		m_dirtyKickouts[Cache::CL_L1D]++;
		// Time for xfer from L1 to L2
		PRINT("Bringing line into L1d.\n");
		PRINT("Add L2 to L1 transfer time (+%d)\n",((L1_block_size / L2_bus_width) * L2_transfer_time));
		m_execTime += (L1_block_size / L2_bus_width) * L2_transfer_time;

	}
}

void Results::L2Evict(Cache::eviction L2Evict)
{
	if (L2Evict == Cache::E_CLEAN)
	{
		m_kickouts[Cache::CL_L2]++;
	}
	else if (L2Evict == Cache::E_DIRTY)
	{
		m_kickouts[Cache::CL_L2]++;
		m_dirtyKickouts[Cache::CL_L2]++;
		// Time for xfer from L2 to main mem
		PRINT("Bringing line into L2.\n");
		PRINT("Add memory to L2 transfer time (+%d)\n",(mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime)));
		m_execTime += mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime);
	}
}

void Results::L1DRef(Cache::checkRet L1DHit)
{
	m_accessTotal[Cache::CL_L1D]++;

	if (L1DHit == Cache::CR_HIT)
	{
		PRINT("Add L1d hit time (+%d)\n",L1_hit_time);
		m_execTime += L1_hit_time;
		m_hitCount[Cache::CL_L1D]++;
	}
	else
	{
		PRINT("Add L1d miss time (+%d)\n",L1_miss_time);
		m_execTime += L1_miss_time;
		// Time for xfer from L2 to L1
		PRINT("Bringing line into L1d.\n");
		PRINT("Add L2 to L1 transfer time (+%d)\n",((L1_block_size / L2_bus_width) * L2_transfer_time));
		m_execTime += (L1_block_size / L2_bus_width) * L2_transfer_time;

		/*Replay time*/
		PRINT("Add L1d hit replay time (+%d)\n",L1_hit_time);
		m_execTime += L1_hit_time;

		m_missCount[Cache::CL_L1D]++;
		m_transfers[Cache::CL_L1D]++;
	}
}

void Results::L2Ref(Cache::checkRet L2Hit)
{
	m_accessTotal[Cache::CL_L2]++;

	if (L2Hit == Cache::CR_HIT)
	{
		PRINT("Add L2 hit time (+%d)\n",L2_hit_time);
		m_execTime += L2_hit_time;
		m_hitCount[Cache::CL_L2]++;
	}
	else
	{
		PRINT("Add L2 miss time (+%d)\n",L2_miss_time);
		m_execTime += L2_miss_time;

		// Time for xfer from main mem to L2
		PRINT("Bringing line into L2.\n");
		PRINT("Add memory to L2 transfer time (+%d)\n",(mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime)));
		m_execTime += mem_sendaddr + mem_ready + ( (L2_block_size / mem_chunksize) * mem_chunktime);

		//Replay time
		PRINT("Add L2 hit replay time (+%d)\n",L2_hit_time);
		m_execTime += L2_hit_time;
		m_missCount[Cache::CL_L2]++;
		m_transfers[Cache::CL_L2]++;
	}
}
void Results::AddExecInfoTime(uint32 execTime)
{
	m_execTime += execTime;
}
uint64 Results::GetExecTime()
{
	return m_execTime;
}




