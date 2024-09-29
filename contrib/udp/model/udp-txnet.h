#ifndef UDP_TX_NET_H
#define UDP_TX_NET_H

#include "ns3/mt-txnet.h"
#include "udp-event.h"

namespace ns3 {
    class UDPTXNetScheduler {
        public:
            // note that the txQueues flow_map could be just a flowMap of PktEvent* queues
            //  instead of event_t *

            UDPTXNetScheduler(int lower_limit, int upper_limit, bool (*drop_policy)(MTEvent *)) : flowMap(queue_set(lower_limit, upper_limit, drop_policy)) {
                eventSelector = flow_map<unsigned int>(0);
                flowSelector = 0;
            }
            ~UDPTXNetScheduler() {}

            UDPTXNetScheduler::get_next_event(PktEvent * e, flow_id id) {
                flowMap[id].enqueue_event(e);
                PktEvent * poppedEvent = flowMap[id].pop();
                pkt_t toReturn = pkt_t(poppedEvent->header, poppedEvent->payload, poppedEvent->src_addr, poppedEvent->dest_addr);
                delete poppedEvent;
                return toReturn;
            }
        
    }
}

#endif 