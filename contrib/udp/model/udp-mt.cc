#include "udp-mt.h"

MTUDP::MTUDP() {
  rxapp = new UDPRXAppParser();
  txnet = new UDPTXNetScheduler();
  rxnet = new UDPRXNetParser();
  scheduler = new UDPScheduler();
  dispatcher = new UDPDispatcher();
  interm_output = new MTIntermediateOutput();
  ctx_table = new flow_map<UDPContext*>();
}

MTUDP::InitContext(flow_id fid) {
  ctx_table[fid] = new UDPContext();
}

MTUDP::~MTUDP() {
  delete rxapp;
  delete txnet;
  delete rxnet;
  delete scheduler;
  delete dispatcher;
  delete interm_output;
  delete ctx_table;
}