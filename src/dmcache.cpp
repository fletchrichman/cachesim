//Direct Mapped Cache: Defines all needed functionality to manipulate the cache
#include "dmcache.h"
#include <iostream>

#define INDEXMASK 0xFFFFFFFF

using namespace std;

DMCache::DMCache(cacheLevel level, uint32 cacheSize, uint32 blockSize)
		:Cache(level){
	cout << "Creating the DM Cache" << endl;

	m_numBlocks = cacheSize / blockSize;							// Calculate number of clocks
	m_blockSize = blockSize;

	int temp = m_numBlocks;											// Calculate number of index bits
	m_numIndexBits = 0;
	while (temp >>= 1){
		m_numIndexBits++;
	}

	temp = m_blockSize;												// Calculate number bits deciding word in block
	m_numBitsWordInBlock = 0;
	while(temp >>= 1){
		m_numBitsWordInBlock++;
	}

	m_numTagBits = WORD_SIZE - m_numIndexBits - m_numBitsWordInBlock;// Calculate number of tag bits
	m_numBitsWordInBlock -= 2;										//Set the number of Bits per word in block

	cout << "NumBlocks:" << m_numBlocks << endl
	     << "NumIndexBits:" << m_numIndexBits << endl
	     << "NumTagBits:" << m_numTagBits << endl
	     << "NumBitsWordInBlock:" << m_numBitsWordInBlock << endl;

	m_cache = new DMCacheBlock[m_numBlocks];
}

uint32 DMCache::getTagFromReference(uint32 reference){
	uint32 tag = reference;											// Calculate tag of reference
	tag = (tag >> (WORD_SIZE - m_numTagBits));

	return tag;
}

uint32 DMCache::getIndexFromReference(uint32 reference){
	uint32 index = reference;										// Calculate index of reference
	uint32 mask = INDEXMASK;										// Shift to right to get number of bits
	mask >>= (WORD_SIZE - m_numIndexBits);
	mask <<= (m_numBitsWordInBlock + m_numBitsByteInWord);			// Shift back into proper location compared to reference
	index = (index & mask);
	index >>= (m_numBitsWordInBlock + m_numBitsByteInWord);

	return index;
}

Cache::checkRet DMCache::checkInCache(uint32 reference){
	uint32 index = getIndexFromReference(reference);
	uint32 tag = getTagFromReference(reference);

	checkRet ret;

	if (m_cache[index].GetTag() == tag && m_cache[index].GetValid()){
		ret = CR_HIT;												// See if reference is in cache
	}
	else{
		ret = CR_MISS;
	}

	return ret;
}

Cache::eviction DMCache::checkAddRequiresEviction(uint32 reference){
	uint32 index = getIndexFromReference(reference);

	if (!m_cache[index].GetValid()){								// If block not yet valid, don't need to evict anything
		return E_NOEVICT;
	}
	else{
		if (m_cache[index].GetDirty()){
			return E_DIRTY;
		}
		else{														// Must evict, either dirty or clean
			return E_CLEAN;
		}

	}
}

uint32 DMCache::getAddressToEvict(uint32 reference){
	uint32 index = getIndexFromReference(reference);
	uint32 evictTag = m_cache[index].GetTag();

	return reconstructAddress(evictTag, index);
}

void DMCache::addToCache(uint32 reference){
	uint32 index = getIndexFromReference(reference);
	uint32 tag = getTagFromReference(reference);

	m_cache[index].SetTag(tag);
	m_cache[index].SetValid(true);
	m_cache[index].SetDirty(false);
}

void DMCache::write(uint32 reference){
	uint32 index = getIndexFromReference(reference);
	m_cache[index].SetDirty(true);
}

uint32 DMCache::reconstructAddress(uint32 tag, uint32 index){
	uint32 addr = (tag << (WORD_SIZE - m_numTagBits)) |
				  (index << (m_numBitsWordInBlock + m_numBitsByteInWord));

	return addr;
}


void DMCache::printCache(){

}
