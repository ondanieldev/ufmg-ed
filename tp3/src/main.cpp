#include <iostream>
#include <string.h>

#include "SearchMachine.h"

using namespace std;

int main(int argc, char **argv)
{
  try
  {
    string corpusDirPath, stopwordsFilePath, queryFilePath, rankingFilePath;

    for (int i = 0; i < argc; i++)
    {
      if (strcmp(argv[i], "-c") == 0)
      {
        corpusDirPath = argv[i + 1];
      }
      else if (strcmp(argv[i], "-s") == 0)
      {
        stopwordsFilePath = argv[i + 1];
      }
      else if (strcmp(argv[i], "-i") == 0)
      {
        queryFilePath = argv[i + 1];
      }
      else if (strcmp(argv[i], "-o") == 0)
      {
        rankingFilePath = argv[i + 1];
      }
    }

    SearchMachine searchMachine = SearchMachine(corpusDirPath, stopwordsFilePath, queryFilePath, rankingFilePath);
    searchMachine.execute();

    return 0;
  }
  catch (const char *msg)
  {
    cerr << "ERROR: " << msg << endl;
  }
}
