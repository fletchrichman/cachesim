#ifndef CACHE_H_
#define CACHE_H_
#include "types.h"

class Cache{
public:
	enum cacheLevel {
		CL_L1I=0,
		CL_L1D,
		CL_L2,
		CL_NUMLEVELS
	};
	
	enum checkRet {
		CR_HIT = 0,
		CR_MISS
	};

	enum eviction {
		E_DIRTY=0,
		E_CLEAN,
		E_NOEVICT,
	};
	
	static Cache* CreateCache(cacheLevel level, uint32 cacheSize, uint32 blockSize, uint32 assoc);
	virtual void write(uint32 reference) = 0;
	virtual void addToCache(uint32 reference) = 0;
	virtual void printCache() = 0;
	virtual uint32 getTagFromReference(uint32 reference) = 0;
	virtual uint32 getIndexFromReference(uint32 reference) = 0;
	virtual checkRet checkInCache(uint32 reference) = 0;
	virtual eviction checkAddRequiresEviction(uint32 reference) = 0;
	virtual uint32 getAddressToEvict(uint32 reference) = 0;

protected:
	Cache(cacheLevel level);
	virtual uint32 reconstructAddress(uint32 tag, uint32 index) = 0;
	virtual ~Cache();

	uint32 m_numBitsWordInBlock;
	uint32 m_numBitsByteInWord;
	uint32 m_blockSize;
	uint32 m_numIndexBits;
	uint32 m_numTagBits;
	cacheLevel m_level;
};


#endif
