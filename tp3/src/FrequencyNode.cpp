#include "FrequencyNode.h"

FrequencyNode::FrequencyNode(int documentId)
{
  this->documentId = documentId;
  this->termFrequency = 1;
  this->wtd = 0;
  this->next = nullptr;
}

FrequencyNode::~FrequencyNode()
{
}

float FrequencyNode::getWtd()
{
  return this->wtd;
}

int FrequencyNode::getDocumentId()
{
  return this->documentId;
}

int FrequencyNode::getTermFrequency()
{
  return this->termFrequency;
}

FrequencyNode *FrequencyNode::getNext()
{
  return this->next;
}

void FrequencyNode::setWtd(float wtd)
{
  this->wtd = wtd;
}

void FrequencyNode::setNext(FrequencyNode *next)
{
  this->next = next;
}

// term frequency always starts with 1 and doesn't have a "set" function. it is just incremented by 1 each time this function is called
void FrequencyNode::incrementTermFrequency()
{
  this->termFrequency += 1;
}
