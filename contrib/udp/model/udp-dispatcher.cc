#include "udp-dispatcher.h"

UDPDispatcher::UDPDispatcher() {
  sendProcessor = new UDPSendProcessor();
  recvProcessor = new UDPRecvProcessor();
  pktProcessor  = new UDPPktProcessor();
  fbProcessor   = new UDPFbProcessor();
  
  eventMap =
    {
      {"SEND", {sendProcessor}},
      {"RECV", {recvProcessor}},
      {"PKT", {pktProcessor}},
      {"FB", {fbProcessor}}
    };
}

UDPDispatcher::~UDPDispatcher() {
  delete sendProcessor;
  delete recvProcessor;
  delete pktProcessor;
  delete fbProcessor;
}

std::vector<MTEventProcessor*> UDPDispatcher::dispatch(MTEvent* event) {
  return eventMap[event->typeString];
}