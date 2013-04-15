/*
 * dmcache.h
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#ifndef DMCACHE_H_
#define DMCACHE_H_

#include "cache.h"
#include "dmcacheblock.h"

class DMCache : public Cache
{
public:
	DMCache(cacheLevel level, uint32 cacheSize, uint32 blockSize);

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

	DMCacheBlock* m_cache;
	uint32 m_numBlocks;
};



#endif /* DMCACHE_H_ */
