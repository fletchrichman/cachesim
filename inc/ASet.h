#ifndef ASet_H_
#define ASet_H_
#include "LRU.h"
#include "types.h"

class ASet{
public:
	ASet();
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

	LRU* m_leastRuNode;
	LRU* m_mostRuNode;
	LRU* m_LRUArray;
};
#endif
