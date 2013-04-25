#ifndef DMBlock_H_
#define DMBlock_H_
#include "types.h"

class DMBlock{
public:
	DMBlock(bool valid = false, bool dirty = false, uint32 tag = 0);
	bool GetDirty();
	void SetDirty(bool dirty);
	bool GetValid();
	void SetValid(bool valid);
	void SetTag(uint32 tag);
	uint32 GetTag();

private:
	bool m_dirty;
	bool m_valid;
	uint32 m_tag;
};
#endif
