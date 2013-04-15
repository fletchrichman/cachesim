/*
 * dmcacheblock.h
 *
 *  Created on: Apr 23, 2012
 *      Author: Tim
 */

#ifndef DMCACHEBLOCK_H_
#define DMCACHEBLOCK_H_

#include "types.h"

class DMCacheBlock
{
public:
	DMCacheBlock(bool valid = false, bool dirty = false, uint32 tag = 0);

	bool GetValid();
	void SetValid(bool valid);

	bool GetDirty();
	void SetDirty(bool dirty);

	uint32 GetTag();
	void SetTag(uint32 tag);
private:
	bool m_valid;
	bool m_dirty;
	uint32 m_tag;
};



#endif /* DMCACHEBLOCK_H_ */
