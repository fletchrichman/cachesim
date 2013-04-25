#ifndef DirectMap_H_
#define DirectMap_H_
#include "Cache.h"
#include "DMBlock.h"

class DirectMap : public Cache{
public:
	void addToCache(uint32 reference);
	void write(uint32 reference);
	void printCache();
	
	eviction checkAddRequiresEviction(uint32 reference);
	uint32 getAddressToEvict(uint32 reference);
	DirectMap(cacheLevel level, uint32 cacheSize, uint32 blockSize);
	uint32 getTagFromReference(uint32 reference);
	uint32 getIndexFromReference(uint32 reference);
	checkRet checkInCache(uint32 reference);

private:
	uint32 reconstructAddress(uint32 tag, uint32 index);
	uint32 m_numBlocks;
	DMBlock* m_cache;
};

#endif