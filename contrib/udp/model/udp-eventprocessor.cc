#include "udp-eventprocessor.h"

EventProcessorOutput* UDPSendProcessor::process(SendEvent * e, EventProcessorOutput* epOut) {

  EventProcessorOutput * newOutput = new EventProcessorOutput;
  newOutput->packets = epOut->packets;
  newOutput->ctx = epOut->ctx;
  newOutput->intermOutput = epOut->intermOutput;

  // construct PktEvent to be added to scheduler
  UDPHeader hdr = UDPHeader(epOut->ctx->src_port, epOut->ctx->dst_port, e->length, 0);
  PktEvent * pktEvent = new PktEvent(e->time, e->flowId, hdr, e->data, epOut->ctx->src_addr, epOut->ctx->dst_addr);
  newOutput->events = {pktEvent};

  // delete SendEvent; we are finished with it 
  delete e;

  return newOutput;
}

bool UDPSendProcessor::isValidEvent(MTEvent* e) {
  return e->typeString == "SEND";
}

EventProcessorOutput* UDPRecvProcessor::process(MTEvent* e, EventProcessorOutput* epOut) {
  std::vector<MTEvent*> newEvents;

  EventProcessorOutput * newOutput = new EventProcessorOutput;
  newOutput->events = epOut->events;
  newOutput->packets = epOut->packets;
  newOutput->ctx = epOut->ctx;
  newOutput->intermOutput = epOut->intermOutput;
  return newOutput;
}

bool UDPRecvProcessor::isValidEvent(MTEvent* e) {
  return e->typeString == "RECV";
}

EventProcessorOutput* UDPPktProcessor::process(MTEvent* e, EventProcessorOutput* epOut) {
  std::vector<MTEvent*> newEvents;

  EventProcessorOutput * newOutput = new EventProcessorOutput;
  newOutput->events = epOut->events;
  newOutput->packets = epOut->packets;
  newOutput->ctx = epOut->ctx;
  newOutput->intermOutput = epOut->intermOutput;
  return newOutput;
}

bool UDPPktProcessor::isValidEvent(MTEvent* e) {
  return e->typeString == "PKT";
}

EventProcessorOutput* UDPFbProcessor::process(MTEvent* e, EventProcessorOutput* epOut) {
  std::vector<MTEvent*> newEvents;

  EventProcessorOutput * newOutput = new EventProcessorOutput;
  newOutput->events = epOut->events;
  newOutput->packets = epOut->packets;
  newOutput->ctx = epOut->ctx;
  newOutput->intermOutput = epOut->intermOutput;
  return newOutput;
}

bool UDPFbProcessor::isValidEvent(MTEvent* e) {
  return e->typeString == "FB";
}





