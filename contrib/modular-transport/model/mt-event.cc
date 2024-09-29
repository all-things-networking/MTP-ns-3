#include "mt-event.h"

namespace ns3 {

  MTEvent::MTEvent(EventType type, EventSubtype subtype, long time, flow_id flowId, std::string typeString):
    type{type},
    subtype{std::move(subtype)},
    time{time},
    flowId{flowId},
    typeString{typeString}
    {
      if (type == EventType::INCOMING && (subtype != EventSubtype::APP_EVENT || subtype != EventSubtype::NET_EVENT)) {
        throw std::runtime_error("Invalid subtype for incoming event");
      }
    }

  MemEvent::MemEvent(long time, flow_id flowId, int32_t atomic_op, addr_t address, int length): 
    MTEvent{EventType::INCOMING, EventSubtype::MEM_EVENT, time, flowId},
    atomic_op{atomic_op},
    address{address},
    length{length}
    {}
  
  UrgentEvent::UrgentEvent(long time, flow_id flowId):
    MTEvent{EventType::INCOMING, EventSubtype::URGENT_EVENT, time, flowId}
  {}

  ProgEvent::ProgEvent(long time, flow_id flowId):
    MTEvent{EventType::INCOMING, EventSubtype::PROG_EVENT, time, flowId}
  {}
 
  TimerEvent::TimerEvent(long time, flow_id flowId):
    MTEvent{EventType::INCOMING, EventSubtype::TIMER_EVENT, time, flowId}
  {}

  NetEvent::NetEvent(EventType type, long time, flow_id flowId):
    MTEvent{type, EventSubtype::NET_EVENT, time, flowId}
  {}

  AppEvent::AppEvent(EventType type, long time, flow_id flowId):
    MTEvent{type, EventSubtype::APP_EVENT, time, flowId}
  {}

} // namespace ns3