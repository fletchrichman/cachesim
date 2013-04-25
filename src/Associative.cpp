//Associative Cache: Defines all needed functionality to manipulate the cache
#include "Associative.h"
#include <iostream>

using namespace std;

Associative::Associative(cacheLevel level, uint32 cacheSize, uint32 blockSize, uint32 assoc)
		 :Cache(level){
	m_numSets = cacheSize / blockSize;						// Calculate number of sets
	m_numSets /= assoc;
	m_blockSize = blockSize;
	m_numWays = assoc;

	uint32 temp = m_numSets;								// Calculate number of index bits
	m_numIndexBits= 0;
	while (temp >>= 1){
		m_numIndexBits++;
	}

	temp = m_blockSize / 4;									// Calculate number of bits deciding word in block
	m_numBitsWordInBlock = 0;
	while (temp >>= 1){
		m_numBitsWordInBlock++;
	}
															// Calculate number of tag bits
	m_numTagBits = WORD_SIZE - m_numIndexBits - m_numBitsByteInWord - m_numBitsWordInBlock;

	m_cache = new ASet[m_numSets];
	uint32 i;
	for (i = 0; i < m_numSets; i++){
		m_cache[i].Init(m_numWays);
	}
}

uint32 Associative::getTagFromReference(uint32 reference){
	return reference >> (WORD_SIZE - m_numTagBits);
}

uint32 Associative::getIndexFromReference(uint32 reference){
	if (m_numIndexBits == 0){
		return 0;
	}
	uint32 index = reference;								// Calculate index of reference
	uint32 mask = 0xFFFFFFFF;
	mask >>= (WORD_SIZE - m_numIndexBits);					// Shift to right to get number of bits
	mask <<= (m_numBitsWordInBlock + m_numBitsByteInWord);
	index = (index & mask);
	index >>= (m_numBitsWordInBlock + m_numBitsByteInWord);	// Shift back into proper location compared to reference
	return index;
}

Cache::checkRet Associative::checkInCache(uint32 reference){
	uint32 tag = getTagFromReference(reference);
	uint32 index = getIndexFromReference(reference);

	bool found = false;
	uint32 way;
	for (way = 0; way < m_numWays; way++){
		if (m_cache[index].getTag(way) == tag && m_cache[index].getValid(way)){
			found = true;
			break;
		}
	}

	if (found){
		m_cache[index].updateLru(way);
		return CR_HIT;
	}
	else{
		return CR_MISS;
	}
}

Cache::eviction Associative::checkAddRequiresEviction(uint32 reference){
	uint32 tag = getTagFromReference(reference);
	uint32 index = getIndexFromReference(reference);

	bool existsEmptyWay = false;
	uint32 emptyWay;
	for (emptyWay = 0; emptyWay < m_numWays; ++emptyWay){
		if (!(m_cache[index].getValid(emptyWay)))
		{
			existsEmptyWay = true;
			break;
		}
	}

	if (existsEmptyWay){
		return E_NOEVICT;
	}
	else{
		uint32 lruWay = m_cache[index].getLruWay();

		bool dirty = m_cache[index].getDirty(lruWay);

		if (dirty){
			return E_DIRTY;
		}
		else{
			return E_CLEAN;
		}
	}
}

uint32 Associative::getAddressToEvict(uint32 reference){
	uint32 index = getIndexFromReference(reference);
	uint32 tag = getTagFromReference(reference);
	uint32 lruWay = m_cache[index].getLruWay();
	uint32 evictTag = m_cache[index].getTag(lruWay);

	return reconstructAddress(evictTag, index);
}

void Associative::addToCache(uint32 reference){
	uint32 index = getIndexFromReference(reference);
	uint32 tag = getTagFromReference(reference);
	bool existsEmptyWay = false;
	uint32 emptyWay;
	for (emptyWay = 0; emptyWay < m_numWays; ++emptyWay){
		if (!(m_cache[index].getValid(emptyWay))){
			existsEmptyWay = true;
			break;
		}
	}

	if (existsEmptyWay){
		m_cache[index].setValid(emptyWay, true);
		m_cache[index].setTag(emptyWay, tag);
		m_cache[index].setDirty(emptyWay, false);

		m_cache[index].updateLru(emptyWay);
	}
	else{
		uint32 lruWay = m_cache[index].getLruWay();

		m_cache[index].setValid(lruWay, true);
		m_cache[index].setTag(lruWay, tag);
		m_cache[index].setDirty(lruWay, false);

		m_cache[index].updateLru(lruWay);
	}
}

void Associative::write(uint32 reference){
	uint32 index = getIndexFromReference(reference);
	uint32 tag = getTagFromReference(reference);

	uint32 i;
	for (i = 0; i < m_numWays; ++i){
		if (m_cache[index].getTag(i) == tag){
			m_cache[index].setDirty(i, true);
			m_cache[index].updateLru(i);
		}
	}
}

uint32 Associative::reconstructAddress(uint32 tag, uint32 index){
	uint32 addr = (tag << (WORD_SIZE - m_numTagBits)) |
				  (index << (m_numBitsWordInBlock + m_numBitsByteInWord));

	return addr;
}

void Associative::printCache(){
	cout << "Memory Level: ";
	switch (m_level){
		case CL_L1I:
			cout << "L1I";
			break;
		case CL_L1D:
			cout << "L1D";
			break;
		case CL_L2:
			cout << "L2";
			break;
	}
	cout << endl;
	cout << hex;

	int i;
	int j;
	for (i = 0; i < m_numSets; ++i){
		cout << "Index: " << i<< " |";
		for (j = 0; j < m_numWays; ++j){
			cout << " V:" << m_cache[i].getValid(j)
				 << " D:" << m_cache[i].getDirty(j)
				 << " Tag:" << m_cache[i].getTag(j)
				 << " |";
		}

		cout << endl;
	}

}




