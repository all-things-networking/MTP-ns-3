#ifndef MT_SCHEDULER_H
#define MT_SCHEDULER_H

#include <vector>
#include <queue>
#include "../helper/mtp-types.h"
#include "mt-event.h"

namespace ns3 {
  class queue_set {
    // queue set
    queue_t<MTEvent *>    appQueue;
    queue_t<MTEvent *>    netQueue;
    queue_t<MTEvent *>   progQueue;
    queue_t<MTEvent *> urgentQueue;
    queue_t<MTEvent *>  timerQueue;
    queue_t<MTEvent *>    memQueue;

    public:
      int total_queues;

      void enqueue_event(MTEvent * event);
      queue_t<MTEvent *> get_queue(int selector);
      void pop_queue(int selector);
      bool is_empty();

      queue_set(int lower_limit, int upper_limit, bool (*drop_policy)(MTEvent *));
  }; 

  class MTScheduler {
    // need to initialize queues (with lower limit, upper limit and drop policy) when pushing
    flow_map<queue_set> flowMap;

    // for choosing next event/flow
    flow_map<unsigned int> eventSelector;
    unsigned int flowSelector;

    public:
      MTScheduler(int lower_limit, int upper_limit, bool (*drop_policy)(MTEvent *));
      ~MTScheduler(){}

      // used to store data from packets belonging to this flow while they are being processed
      //flow_map<stream> transitoryMemory;

      void enqueue_event(flow_id id, MTEvent * event);
      void initialize();
      flow_id next_flow();
      MTEvent * next_event_by_id(flow_id id);

      bool is_empty();
 
      MTEvent * get_next_event();
  };
}

#endif