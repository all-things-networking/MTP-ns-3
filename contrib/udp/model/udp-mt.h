#ifndef MTUDP_H
#define MTUDP_H

#include "ns3/modular-transport.h"
#include "ns3/mt-context.h"

class MTUDP: public ns3::ModularTransport
{
  private:
    /* data */
  public:
    MTUDP();
    ~MTUDP();
    ns3::MTContext* InitContext(flow_id fid) override;
};

#endif