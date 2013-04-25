#include "Cache.h"

#include "DirectMap.h"
#include "Associative.h"

Cache::Cache(cacheLevel level)
     : m_level(level),
	   m_numBitsByteInWord(2){
}															

Cache::~Cache(){
}															

Cache* Cache::CreateCache(cacheLevel level, uint32 cacheSize, uint32 blockSize, uint32 assoc){
	if (assoc == 1){
		return new DirectMap(level, cacheSize, blockSize);
	}
	else{
		return new Associative(level, cacheSize, blockSize, assoc);
	}
}



