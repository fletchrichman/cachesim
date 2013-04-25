//configure variables
#include "config.h"

#include <iostream>

#include "INIReader.h"

#define L1CACHESECTION "L1Cache"
#define L2CACHESECTION "L2Cache"
#define MAINMEMSECTION "MainMem"

// L1 cache configuration variables
uint32 L1_block_size;
uint32 L1_cache_size;
uint32 L1_assoc;
uint32 L1_hit_time;
uint32 L1_miss_time;

// L2 cache configuration variables
uint32 L2_block_size;
uint32 L2_cache_size;
uint32 L2_assoc;
uint32 L2_hit_time;
uint32 L2_miss_time;
uint32 L2_transfer_time;
uint32 L2_bus_width;

// Main memory configuration values
uint32 mem_sendaddr;
uint32 mem_ready;
uint32 mem_chunktime;
uint32 mem_chunksize;

using namespace std;

bool Config::readConfigFile(string filename)
{
	INIReader reader(filename);

	if (reader.ParseError() < 0)
	{
		cout << filename << endl;
		return false;
	}

	// Read L1 config variables from file
	L1_block_size = reader.GetInteger(L1CACHESECTION, "L1_block_size", 0);
	L1_cache_size = reader.GetInteger(L1CACHESECTION, "L1_cache_size", 0);
	L1_assoc = reader.GetInteger(L1CACHESECTION, "L1_assoc", 0);
	L1_hit_time = reader.GetInteger(L1CACHESECTION, "L1_hit_time", 0);
	L1_miss_time = reader.GetInteger(L1CACHESECTION, "L1_miss_time", 0);

	// Read L2 config variables from file
	L2_block_size = reader.GetInteger(L2CACHESECTION, "L2_block_size", 0);
	L2_cache_size = reader.GetInteger(L2CACHESECTION, "L2_cache_size", 0);
	L2_assoc = reader.GetInteger(L2CACHESECTION, "L2_assoc", 0);
	L2_hit_time = reader.GetInteger(L2CACHESECTION, "L2_hit_time", 0);
	L2_miss_time = reader.GetInteger(L2CACHESECTION, "L2_miss_time", 0);
	L2_transfer_time = reader.GetInteger(L2CACHESECTION, "L2_transfer_time", 0);
	L2_bus_width = reader.GetInteger(L2CACHESECTION, "L2_bus_width", 0);

	// Read main mem config variables from file
	mem_sendaddr = reader.GetInteger(MAINMEMSECTION, "mem_sendaddr", 0);
	mem_ready = reader.GetInteger(MAINMEMSECTION, "mem_ready", 0);
	mem_chunktime = reader.GetInteger(MAINMEMSECTION, "mem_chunktime", 0);
	mem_chunksize = reader.GetInteger(MAINMEMSECTION, "mem_chunksize", 0);

	return true;
}
