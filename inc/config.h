#ifndef CONFIG_H_
#define CONFIG_H_
#include <string>
#include "types.h"

//L1 cache configuration variables
extern uint32 L1_block_size;
extern uint32 L1_cache_size;
extern uint32 L1_assoc;
extern uint32 L1_hit_time;
extern uint32 L1_miss_time;

//L2 cache configuration variables
extern uint32 L2_block_size;
extern uint32 L2_cache_size;
extern uint32 L2_assoc;
extern uint32 L2_hit_time;
extern uint32 L2_miss_time;
extern uint32 L2_transfer_time;
extern uint32 L2_bus_width;

//Main memory configuration values
extern uint32 mem_sendaddr;
extern uint32 mem_ready;
extern uint32 mem_chunktime;
extern uint32 mem_chunksize;

using namespace std;

class Config{
public:
	static bool readConfigFile(string filename);
};
#endif
