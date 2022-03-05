#include "RankingNode.h"

RankingNode::RankingNode()
{
  this->documentId = -1;
  this->sim = 0;
  this->wd2 = 0;
}

RankingNode::~RankingNode()
{
}

int RankingNode::getDocumentId()
{
  return this->documentId;
}

void RankingNode::setDocumentId(int documentId)
{
  this->documentId = documentId;
}

// wd2 always starts with 0 and doesn't have a "set" function. it is just incremented by the given param each time this function is called
void RankingNode::increaseWd2(float wd2)
{
  this->wd2 += wd2;
}

void RankingNode::setSim(float sim)
{
  this->sim = sim;
}

float RankingNode::getWd2()
{
  return this->wd2;
}

float RankingNode::getSim()
{
  return this->sim;
}
