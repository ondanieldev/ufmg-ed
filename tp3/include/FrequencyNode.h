#ifndef FREQUENCYNODE_H
#define FREQUENCYNODE_H

class FrequencyNode
{
public:
  FrequencyNode(int documentId);
  ~FrequencyNode();
  float getWtd();
  int getDocumentId();
  int getTermFrequency();
  FrequencyNode *getNext();
  void setWtd(float wtd);
  void setNext(FrequencyNode *next);
  void incrementTermFrequency();

private:
  float wtd;
  int documentId;
  int termFrequency;

  FrequencyNode *next;
};

#endif