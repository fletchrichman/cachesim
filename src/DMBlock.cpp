//Direct Mapped Cache Block: Simple functionality for DM Cache blocks
#include "DMBlock.h"

DMBlock::DMBlock(bool valid, bool dirty, uint32 tag)
			 : m_valid(valid),
			   m_dirty(dirty),
			   m_tag(tag){
}																		

bool DMBlock::GetValid(){
	return m_valid;
}

void DMBlock::SetValid(bool valid){
	m_valid = valid;
}

bool DMBlock::GetDirty(){
	return m_dirty;
}

void DMBlock::SetDirty(bool dirty){
	m_dirty = dirty;
}

uint32 DMBlock::GetTag(){
	return m_tag;
}

void DMBlock::SetTag(uint32 tag){
	m_tag = tag;
}



