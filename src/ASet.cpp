//Associtive Cache Set: Simple LRU functionality for associative cache
#include "ASet.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

ASet::ASet(){
}																	

void ASet::Init(uint32 numWays){
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

bool ASet::getValid(uint32 way){
	return m_valids[way];
}

void ASet::setValid(uint32 way, bool valid){
	m_valids[way] = valid;
}

bool ASet::getDirty(uint32 way){
	return m_dirtys[way];
}

void ASet::setDirty(uint32 way, bool dirty){
	m_dirtys[way] = dirty;
}

uint32 ASet::getTag(uint32 way){
	return m_tags[way];
}

void ASet::setTag(uint32 way, uint32 tag){
	m_tags[way] = tag;
}

uint32 ASet::getLruWay(){
	return m_leastRuNode->getWay();
}

void ASet::updateLru(uint32 usedWay){
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

