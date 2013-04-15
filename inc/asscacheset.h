/*
 * asscacheset.h
 *
 *  Created on: May 1, 2012
 *      Author: Tim
 */

#ifndef ASSCACHESET_H_
#define ASSCACHESET_H_

#include "lrunode.h"
#include "types.h"

class AssCacheSet
{
public:
	AssCacheSet();
	void Init(uint32 numWays);

	bool getValid(uint32 way);
	void setValid(uint32 way, bool valid);

	bool getDirty(uint32 way);
	void setDirty(uint32 way, bool dirty);

	uint32 getTag(uint32 way);
	void setTag(uint32 way, uint32 tag);

	uint32 getLruWay();
	void updateLru(uint32 usedWay);

private:
	bool* m_valids;
	bool* m_dirtys;

	uint32*  m_tags;

	LruNode* m_leastRuNode;
	LruNode* m_mostRuNode;
	LruNode* m_lruNodeArray;
};



#endif /* ASSCACHESET_H_ */
