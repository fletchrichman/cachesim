//Associtive Cache Set: Simple LRU functionality for associative cache
#include "asscacheset.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

AssCacheSet::AssCacheSet(){
}																	

void AssCacheSet::Init(uint32 numWays){
	m_valids  = new bool[numWays]();								// Create valid, dirty, and tag arrays
	m_dirtys  = new bool[numWays]();
	m_tags    = new uint32[numWays];

	m_LRUArray = new LRU[numWays]();						// Create the lru list nodes
	m_LRUArray[0].setPrev(NULL);								// Link the lru list nodes
	int i;
	for (i = 0; i < numWays - 1; ++i){
		m_LRUArray[i].setWay(i);

		m_LRUArray[i].setNext(&m_LRUArray[i+1]);
		m_LRUArray[i+1].setPrev(&m_LRUArray[i]);
	}
	m_LRUArray[numWays-1].setWay(numWays-1);
	m_LRUArray[numWays-1].setNext(NULL);
	m_mostRuNode = &m_LRUArray[0];								// List is in order of creation
	m_leastRuNode = &m_LRUArray[numWays-1];
}

bool AssCacheSet::getValid(uint32 way){
	return m_valids[way];
}

void AssCacheSet::setValid(uint32 way, bool valid){
	m_valids[way] = valid;
}

bool AssCacheSet::getDirty(uint32 way){
	return m_dirtys[way];
}

void AssCacheSet::setDirty(uint32 way, bool dirty){
	m_dirtys[way] = dirty;
}

uint32 AssCacheSet::getTag(uint32 way){
	return m_tags[way];
}

void AssCacheSet::setTag(uint32 way, uint32 tag){
	m_tags[way] = tag;
}

uint32 AssCacheSet::getLruWay(){
	return m_leastRuNode->getWay();
}

void AssCacheSet::updateLru(uint32 usedWay){
	if (usedWay != 0){
		int x = 3;
	}

	LRU* usedLRU = &m_LRUArray[usedWay];

	if (usedLRU == m_mostRuNode){								// If we just used the already MRU, nothing to do
		return;
	}

	LRU* lruUsedNext = usedLRU->getNext();					// Get the nodes directly before and after the one node of the found access
	LRU* lruUsedPrev = usedLRU->getPrev();

	if (usedLRU == m_leastRuNode){
		m_leastRuNode = lruUsedPrev;								// If used was LRU, LRU is now its previous
	}

	
	if (lruUsedNext != NULL){
		lruUsedNext->setPrev(lruUsedPrev);							// Remove the used node from the list
	}
	lruUsedPrev->setNext(lruUsedNext);
	m_mostRuNode->setPrev(usedLRU);								// Insert used to front of list
	usedLRU->setNext(m_mostRuNode);
	usedLRU->setPrev(NULL);
	m_mostRuNode = usedLRU;										// Used is now LRUs
}

