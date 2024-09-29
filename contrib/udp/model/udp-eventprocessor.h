#ifndef UDP_EVENTPROCESSOR_H
#define UDP_EVENTPROCESSOR_H

#include "ns3/mt-eventprocessor.h>"

namespace ns3 {
  class UDPSendProcessor: public MTEventProcessor {
    public:
      UDPSendProcessor() {}
      ~UDPSendProcessor() {}
      EventProcessorOutput* process(SendEvent * e, EventProcessorOutput* epOut);
      bool isValidEvent(MTEvent* e);
  };

  class UDPRecvProcessor : public MTEventProcessor {
    public:
      UDPRecvProcessor() {}
      ~UDPRecvProcessor() {}
      EventProcessorOutput* process(MTEvent* e, EventProcessorOutput* epOut);
      bool isValidEvent(MTEvent* e);
  };

  class UDPPktProcessor : public MTEventProcessor {
    public:
      UDPPktProcessor() {}
      ~UDPPktProcessor() {}
      EventProcessorOutput* process(MTEvent* e, EventProcessorOutput* epOut);
      bool isValidEvent(MTEvent* e);
  };

  class UDPFbProcessor : public MTEventProcessor {
    public:
      UDPFbProcessor() {}
      ~UDPFbProcessor() {}
      EventProcessorOutput* process(MTEvent* e, EventProcessorOutput* epOut);
      bool isValidEvent(MTEvent* e);
  };
}

#endif