/*
 * cache.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#include "cache.h"

#include "dmcache.h"
#include "asscache.h"

Cache::Cache(cacheLevel level)
     : m_level(level),
	   m_numBitsByteInWord(2)
{
	// Empty on purpose
}

Cache::~Cache()
{
	// Empty on purpose
}

Cache* Cache::CreateCache(cacheLevel level, uint32 cacheSize, uint32 blockSize, uint32 assoc)
{
	if (assoc == 1)
	{
		return new DMCache(level, cacheSize, blockSize);
	}
	else
	{
		return new AssCache(level, cacheSize, blockSize, assoc);
	}
}



