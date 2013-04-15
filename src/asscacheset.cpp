/*
 * asscacheset.cpp
 *
 *  Created on: May 1, 2012
 *      Author: Tim
 */

#include "asscacheset.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

AssCacheSet::AssCacheSet()
{
	// Empty on purpose, must call init to allocate arrays
}

void AssCacheSet::Init(uint32 numWays)
{
	// Create valid, dirty, and tag arrays
	m_valids  = new bool[numWays]();
	m_dirtys  = new bool[numWays]();
	m_tags    = new uint32[numWays];

	// Create the lru list nodes
	m_lruNodeArray = new LruNode[numWays]();
	// Link the lru list nodes
	m_lruNodeArray[0].setPrev(NULL);
	int i;
	for (i = 0; i < numWays - 1; ++i)
	{
		m_lruNodeArray[i].setWay(i);

		m_lruNodeArray[i].setNext(&m_lruNodeArray[i+1]);
		m_lruNodeArray[i+1].setPrev(&m_lruNodeArray[i]);
	}
	m_lruNodeArray[numWays-1].setWay(numWays-1);
	m_lruNodeArray[numWays-1].setNext(NULL);

	// For now list is in order of creation
	m_mostRuNode = &m_lruNodeArray[0];
	m_leastRuNode = &m_lruNodeArray[numWays-1];
}

bool AssCacheSet::getValid(uint32 way)
{
	return m_valids[way];
}

void AssCacheSet::setValid(uint32 way, bool valid)
{
	m_valids[way] = valid;
}

bool AssCacheSet::getDirty(uint32 way)
{
	return m_dirtys[way];
}

void AssCacheSet::setDirty(uint32 way, bool dirty)
{
	m_dirtys[way] = dirty;
}

uint32 AssCacheSet::getTag(uint32 way)
{
	return m_tags[way];
}

void AssCacheSet::setTag(uint32 way, uint32 tag)
{
	m_tags[way] = tag;
}

uint32 AssCacheSet::getLruWay()
{
	return m_leastRuNode->getWay();
}

void AssCacheSet::updateLru(uint32 usedWay)
{
	if (usedWay != 0)
	{
		int x = 3;
	}

	LruNode* usedLruNode = &m_lruNodeArray[usedWay];

	// If we just used the already MRU, nothing to do
	if (usedLruNode == m_mostRuNode)
	{
		return;
	}

	// Get the nodes directly before and after the one node of the found access
	LruNode* lruUsedNext = usedLruNode->getNext();
	LruNode* lruUsedPrev = usedLruNode->getPrev();

	// If used was LRU, LRU is now its previous
	if (usedLruNode == m_leastRuNode)
	{
		m_leastRuNode = lruUsedPrev;
	}

	// Remove the used node from the list
	if (lruUsedNext != NULL)
	{
		lruUsedNext->setPrev(lruUsedPrev);
	}
	lruUsedPrev->setNext(lruUsedNext);

	// Insert used to front of list
	m_mostRuNode->setPrev(usedLruNode);
	usedLruNode->setNext(m_mostRuNode);
	usedLruNode->setPrev(NULL);

	// Used is now LRUs
	m_mostRuNode = usedLruNode;
}

