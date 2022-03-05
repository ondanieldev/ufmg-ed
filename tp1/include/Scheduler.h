#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>

#include "Queue.h"
#include "List.h"

class Scheduler
{
public:
  Scheduler();
  void addUrl(std::string urlName);
  void scheduleAll();
  void scheduleByQuantity(int quantity);
  void scheduleByHost(std::string hostName, int quantity);
  void showHost(std::string hostName);
  void indexHosts();
  void clearHost(std::string hostName);

private:
  Queue hosts;
};

#endif