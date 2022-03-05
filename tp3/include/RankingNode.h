#ifndef RANKINGNODE_H
#define RANKINGNODE_H

class RankingNode
{
public:
  RankingNode();
  ~RankingNode();
  float getWd2();
  float getSim();
  int getDocumentId();
  void setSim(float sim);
  void setDocumentId(int documentId);
  void increaseWd2(float wd);

private:
  int documentId;
  float wd2;
  float sim;
};

#endif