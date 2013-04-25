//Linked List implementation for LRU
#include "LRU.h"
LRU::LRU(){}

void LRU::setWay(uint32 way){
	m_way = way;
}

uint32 LRU::getWay(){
	return m_way;
}

void LRU::setNext(LRU* next){
	m_next = next;
}

LRU* LRU::getNext(){
	return m_next;
}

void LRU::setPrev(LRU* prev){
	m_prev = prev;
}

LRU* LRU::getPrev(){
	return m_prev;
}







