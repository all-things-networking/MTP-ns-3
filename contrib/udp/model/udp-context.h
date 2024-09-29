#ifndef UDP_CONTEXT_H
#define UDP_CONTEXT_H

using namespace std;

#include "../../modular-transport/model/mt-context.h"

namespace ns3 {
  class UDPContext: public MTContext {
    public:
      Ipv4Address src_addr;
      Ipv4Address dst_addr;
      int src_port;
      int dst_port;
      int sent_count;
      int recv_count;
      int MTU = 3;
  };
}

#endif