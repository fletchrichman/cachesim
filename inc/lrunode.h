/*
 * lrunode.h
 *
 *  Created on: May 1, 2012
 *      Author: Tim
 */

#ifndef LRUNODE_H_
#define LRUNODE_H_

#include "types.h"

class LruNode
{
public:
	LruNode();

	LruNode* getNext();
	void setNext(LruNode* next);
	LruNode* getPrev();
	void setPrev(LruNode* prev);
	uint32 getWay();
	void setWay(uint32 way);
private:
	LruNode* m_next;
	LruNode* m_prev;

	uint32 m_way;
};


#endif /* LRUNODE_H_ */
