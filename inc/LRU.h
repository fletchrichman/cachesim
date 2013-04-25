/*
 * LRU.h
 *
 *  Created on: May 1, 2012
 *      Author: Tim
 */

#ifndef LRU_H_
#define LRU_H_

#include "types.h"

class LRU
{
public:
	LRU();

	LRU* getNext();
	void setNext(LRU* next);
	LRU* getPrev();
	void setPrev(LRU* prev);
	uint32 getWay();
	void setWay(uint32 way);
private:
	LRU* m_next;
	LRU* m_prev;

	uint32 m_way;
};


#endif /* LRU_H_ */
