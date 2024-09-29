#ifndef MT_TX_NET_H
#define MT_TX_NET_H

#include "mt-scheduler.h"
#include "ns3/flow-map.h"

namespace ns3 {
  class MTTXNetScheduler {
    flow_map<queue_t<event_t *>> txQueues;

    // for choosing next event/flow
    flow_map<unsigned int> eventSelector;
    unsigned int flowSelector;

    public:
      MTTXNetScheduler();
      virtual ~MTTXNetScheduler();

      // initialize queues here
      virtual void initialize();
      virtual pkt_t get_next_packet(MTEvent * event);
  };
}

#endif