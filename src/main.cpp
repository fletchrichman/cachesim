/*
 * main.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#include <iostream>
#include <cstdlib>

#include "config.h"
#include "cache.h"
#include "trace.h"
#include "results.h"
#include "dmcache.h"
#include "asscache.h"
#include "simulator.h"

#define BASE 0
#define L12WAY 1
#define L22WAY 2
#define ALL2WAY 3
#define L12WAYL24WAY 4
#define L2BIG 5
#define ALLFA 6

#define INPUTTRACE "stdin"
//#define INPUTTRACE "./long-trace/test.txt"
inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}
extern bool printBool;
int main(int argc, char **argv)
{
	int whichConfig=0;
	uint64 tempTime=0;
	whichConfig=atoi(argv[1]);
	switch(whichConfig)
	{
		case BASE:
			printf("Using Base Config\n");
			Config::readConfigFile("./configs/parametersBase.conf");
			break;
		case L12WAY:
			printf("Using L1 2-Way Config\n");
			Config::readConfigFile("./configs/parametersL12.conf");
			break;
		case L22WAY:
			printf("Using L2 2-Way Config\n");
			Config::readConfigFile("./configs/parametersL22.conf");
			break;
		case ALL2WAY:
			printf("Using All 2-way Config\n");
			Config::readConfigFile("./configs/parametersAll2.conf");
			break;
		case L12WAYL24WAY:
			printf("Using L12WAYL24WAY Config\n");
			Config::readConfigFile("./configs/parametersL12L24.conf");
			break;
		case L2BIG:
			printf("Using L2BIG Config\n");
			Config::readConfigFile("./configs/parametersL2Big.conf");
			break;
		case ALLFA:
			printf("Using ALL FA Config\n");
			Config::readConfigFile("./configs/parametersAllFA.conf");
			break;

		default:
			printf("Invalid Configuration File Number:%d\n",whichConfig);
			break;
	}
/*
	Cache* L1I = new DMCache(Cache::CL_L1I, L1_cache_size, L1_block_size);
	Cache* L1D = new DMCache(Cache::CL_L1D, L1_cache_size, L1_block_size);

	Cache* L2 = new DMCache(Cache::CL_L2, L2_cache_size, L2_block_size);
	*/
	Cache* L1I = Cache::CreateCache(Cache::CL_L1I, L1_cache_size, L1_block_size, L1_assoc);
	Cache* L1D = Cache::CreateCache(Cache::CL_L1D, L1_cache_size, L1_block_size, L1_assoc);
	Cache* L2 = Cache::CreateCache(Cache::CL_L2, L2_cache_size, L2_block_size, L2_assoc);

	Trace::OpenTraceFile(INPUTTRACE);

	Instruction* instr = new Instruction();
	Results* results = new Results();
	if (argc < 2)
	{
		printBool=false;
	}
	else if(argv[2] != NULL)
	{
		if (atoi(argv[2]) == 1) printBool=true;
	}

	printf("Status of printing: %s\n",BoolToString(printBool));

	while (Trace::GetInstruction(instr, results) == 0)
	{
		tempTime=results->GetExecTime();
		if(printBool == true) Trace::PrintInstruction(instr);
		Simulator::HandleInstruction(instr, L1I, L1D, L2, results);
		tempTime=results->GetExecTime()-tempTime;
		results->AddCycleCount(instr->GetOpcode(),tempTime);
		if(printBool == true) printf("Simulated Time = %llu\n",results->GetExecTime());
	}

	results->PrintResults();

	//L1I->printCache();

	return 0;
}

