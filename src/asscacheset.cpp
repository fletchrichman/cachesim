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

	m_lruNodeArray = new LruNode[numWays]();						// Create the lru list nodes
	m_lruNodeArray[0].setPrev(NULL);								// Link the lru list nodes
	int i;
	for (i = 0; i < numWays - 1; ++i){
		m_lruNodeArray[i].setWay(i);

		m_lruNodeArray[i].setNext(&m_lruNodeArray[i+1]);
		m_lruNodeArray[i+1].setPrev(&m_lruNodeArray[i]);
	}
	m_lruNodeArray[numWays-1].setWay(numWays-1);
	m_lruNodeArray[numWays-1].setNext(NULL);
	m_mostRuNode = &m_lruNodeArray[0];								// List is in order of creation
	m_leastRuNode = &m_lruNodeArray[numWays-1];
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

	LruNode* usedLruNode = &m_lruNodeArray[usedWay];

	if (usedLruNode == m_mostRuNode){								// If we just used the already MRU, nothing to do
		return;
	}

	LruNode* lruUsedNext = usedLruNode->getNext();					// Get the nodes directly before and after the one node of the found access
	LruNode* lruUsedPrev = usedLruNode->getPrev();

	if (usedLruNode == m_leastRuNode){
		m_leastRuNode = lruUsedPrev;								// If used was LRU, LRU is now its previous
	}

	
	if (lruUsedNext != NULL){
		lruUsedNext->setPrev(lruUsedPrev);							// Remove the used node from the list
	}
	lruUsedPrev->setNext(lruUsedNext);
	m_mostRuNode->setPrev(usedLruNode);								// Insert used to front of list
	usedLruNode->setNext(m_mostRuNode);
	usedLruNode->setPrev(NULL);
	m_mostRuNode = usedLruNode;										// Used is now LRUs
}

