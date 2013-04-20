//Direct Mapped Cache Block: Simple functionality for DM Cache blocks
#include "dmcacheblock.h"

DMCacheBlock::DMCacheBlock(bool valid, bool dirty, uint32 tag)
			 : m_valid(valid),
			   m_dirty(dirty),
			   m_tag(tag){
}																		

bool DMCacheBlock::GetValid(){
	return m_valid;
}

void DMCacheBlock::SetValid(bool valid){
	m_valid = valid;
}

bool DMCacheBlock::GetDirty(){
	return m_dirty;
}

void DMCacheBlock::SetDirty(bool dirty){
	m_dirty = dirty;
}

uint32 DMCacheBlock::GetTag(){
	return m_tag;
}

void DMCacheBlock::SetTag(uint32 tag){
	m_tag = tag;
}



