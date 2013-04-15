/*
 * asscache.h
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#ifndef ASSCACHE_H_
#define ASSCACHE_H_

#include "cache.h"
#include "asscacheset.h"
#include "lrunode.h"

class AssCache : public Cache
{
public:
	AssCache(cacheLevel level, uint32 cacheSize, uint32 blockSize, uint32 assoc);

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

	AssCacheSet* m_cache;

	uint32 m_numSets;
	uint32 m_numWays;
};




#endif /* ASSCACHE_H_ */
