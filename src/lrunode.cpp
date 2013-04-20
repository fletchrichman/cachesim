//Linked List implementation for LRU
#include "lrunode.h"
LruNode::LruNode(){}

void LruNode::setWay(uint32 way){
	m_way = way;
}

uint32 LruNode::getWay(){
	return m_way;
}

void LruNode::setNext(LruNode* next){
	m_next = next;
}

LruNode* LruNode::getNext(){
	return m_next;
}

void LruNode::setPrev(LruNode* prev){
	m_prev = prev;
}

LruNode* LruNode::getPrev(){
	return m_prev;
}







