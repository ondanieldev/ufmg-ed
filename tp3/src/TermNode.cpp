#include "TermNode.h"

TermNode::TermNode(std::string term)
{
  this->term = term;
  this->frequencyList = new FrequencyList();
  this->next = nullptr;
}

TermNode::~TermNode()
{
}

TermNode *TermNode::getNext()
{
  return this->next;
}

std::string TermNode::getTerm()
{
  return this->term;
}

FrequencyList *TermNode::getFrequencyList()
{
  return this->frequencyList;
}

void TermNode::setNext(TermNode *next)
{
  this->next = next;
}
