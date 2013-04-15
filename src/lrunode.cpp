/*
 * lrunode.cpp
 *
 *  Created on: May 1, 2012
 *      Author: Tim
 */

#include "lrunode.h"

LruNode::LruNode()
{
	// Empty on purpose
}

LruNode* LruNode::getNext()
{
	return m_next;
}

void LruNode::setNext(LruNode* next)
{
	m_next = next;
}

LruNode* LruNode::getPrev()
{
	return m_prev;
}

void LruNode::setPrev(LruNode* prev)
{
	m_prev = prev;
}

uint32 LruNode::getWay()
{
	return m_way;
}

void LruNode::setWay(uint32 way)
{
	m_way = way;
}


