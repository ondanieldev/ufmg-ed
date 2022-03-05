#include <iostream>
#include <dirent.h>

#include "Page.h"
#include "Storage.h"
#include "Heapsort.h"
#include "Quicksort.h"

std::string Storage::getTapePath(int i)
{
  return "./tmp/rodada-" + std::to_string(i) + ".txt";
}

void Storage::resetTapesDir()
{
  DIR *tapesFolder = opendir("./tmp");
  struct dirent *nextTape;
  char tapePath[256];

  while ((nextTape = readdir(tapesFolder)) != NULL)
  {
    sprintf(tapePath, "%s/%s", "./tmp", nextTape->d_name);
    remove(tapePath);
  }
  closedir(tapesFolder);
}

void Storage::populateTape(std::fstream &input, std::fstream &tape, int maxEntities)
{

  // each page class and its props
  std::string url;
  int popularity;
  Page page;

  // all pages
  Page pages[maxEntities];
  int pagesSize = 0;

  // get pages from input file and save as an array
  for (int i = 0; i < maxEntities && !input.eof(); ++i)
  {
    input >> url >> popularity;
    page.setUrl(url);
    page.setPopularity(popularity);
    pages[i] = page;
    pagesSize++;
  }

  // order pages
  Quicksort::quicksort(pages, pagesSize);

  // insert pages into tape
  for (int i = 0; i < pagesSize; ++i)
  {
    tape << pages[i].getUrl() << " " << pages[i].getPopularity() << std::endl;
  }
}

void Storage::generateTapes(std::fstream &input, int maxTapes, int maxEntities)
{
  // initialize tape path
  std::string tapePath;

  // generate each tape
  for (int i = 1; i <= maxTapes && !input.eof(); ++i)
  {
    // crate tape
    tapePath = Storage::getTapePath(i);
    std::fstream tape(tapePath, std::fstream::out);
    tape.close();

    // open tape
    tape.open(tapePath);
    if (!tape)
    {
      throw std::invalid_argument("could not generate a new tape");
    }

    // populate tape
    Storage::populateTape(input, tape, maxEntities);

    // close tape
    tape.close();
  }
}

void Storage::mergeTapes(std::fstream &output, int maxTapes)
{

  // all pages
  Page pages[maxTapes];
  int pagesSize = 0;

  // current page
  Page page;
  std::string url;
  int popularity, pageTape;

  // all tapes
  std::fstream tapes[maxTapes];

  // current tape
  std::string tapePath;

  // get one page per tape and open all tapes
  for (int i = 1; i <= maxTapes; ++i)
  {
    tapePath = Storage::getTapePath(i);
    tapes[i - 1].open(tapePath);
    if (tapes[i - 1].fail())
    {
      break;
    }
    tapes[i - 1] >> url >> popularity;
    page.setUrl(url);
    page.setPopularity(popularity);
    page.setTape(i);
    pages[i - 1] = page;
    pagesSize++;
  }

  // order pages
  Heapsort::heapsort(pages, pagesSize);

  // merge tapes until all pages get read
  while (pagesSize > 0)
  {
    // get the most popular page
    page = Heapsort::pop(pages, &pagesSize);

    // put page into output file
    output << page.getUrl() << " " << page.getPopularity() << std::endl;

    // get a new page from the same tape
    pageTape = page.getTape();

    // if still there is a page on the tape, add it to the heap
    if (tapes[pageTape - 1] >> url >> popularity)
    {
      page.setUrl(url);
      page.setPopularity(popularity);
      page.setTape(pageTape); // as the page variable is being reused, it is not necessary to write this line, but it is good to let it explicit
      pages[pagesSize] = page;
      pagesSize++;
      Heapsort::heapsort(pages, pagesSize);
    }
    // otherwise, close the tape
    else
    {
      tapes[pageTape - 1].close();
    }
  }
}