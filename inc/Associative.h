#ifndef Associative_H_
#define Associative_H_
#include "Cache.h"
#include "ASet.h"
#include "LRU.h"

class Associative : public Cache{
public:
	Associative(cacheLevel level, uint32 cacheSize, uint32 blockSize, uint32 assoc);
	uint32 getTagFromReference(uint32 reference);
	uint32 getIndexFromReference(uint32 reference);
	checkRet checkInCache(uint32 reference);
	eviction checkAddRequiresEviction(uint32 reference);
	uint32 getAddressToEvict(uint32 reference);
	void addToCache(uint32 reference);
	void write(uint32 reference);
	void printCache();
private:
	uint32 reconstructAddress(uint32 tag, uint32 index);
	ASet* m_cache;
	uint32 m_numSets;
	uint32 m_numWays;
};
#endif
