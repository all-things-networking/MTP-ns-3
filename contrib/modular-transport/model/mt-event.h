#ifndef MT_EVENT_H
#define MT_EVENT_H

#include <variant> // std::variant
#include <cstdint> // int32_t
#include <stdexcept> // std::runtime_error
#include <string>
#include "../helper/mtp-types.h"

namespace ns3{

// TODO: Do we need to implement a TX_EVENT type (from page 27 of the Overleaf doc) ?

class MTHeader;

enum EventType {
    INCOMING, // event that transfers nothing to outer layers
    OUTGOING,  // event that transfers packets or feedback to outer layers
    NONE
};

enum EventSubtype {
    APP_EVENT,
    NET_EVENT,
    TIMER_EVENT,
    PROG_EVENT,
    URGENT_EVENT,
    MEM_EVENT,
    ERROR_EVENT
};

class MTEvent {
    public:
        EventType type;
        EventSubtype subtype;
        long time;
        flow_id flowId;
        const std::string typeString;
        virtual EventType getType() { return type; }

        // used as key in event processor's eventMap
        std::string name;

        MTEvent(EventType type, 
                EventSubtype subtype,
                long time, 
                flow_id flowId,
                std::string typeString = "");
        virtual ~MTEvent();
};

class MemEvent : public MTEvent {
    public:
        int32_t atomic_op;
        addr_t address;
        int length;

        MemEvent(long time, 
                flow_id flowId, 
                int32_t atomic_op, 
                addr_t address, 
                int length);
        ~MemEvent() override;
};

class UrgentEvent : public MTEvent {
    public:
        UrgentEvent(long time, 
                    flow_id flowId);
        ~UrgentEvent() override;
};

class ProgEvent : public MTEvent {
    public:
        ProgEvent(long time, 
                flow_id flowId);
        ~ProgEvent() override;
};

class TimerEvent : public MTEvent {
    public:
        TimerEvent(long time, flow_id flowId);
        ~TimerEvent() override;
};

class NetEvent : public MTEvent {
    public:
        NetEvent(EventType type,
                long time, 
                flow_id flowId);
        ~NetEvent() override;
};

class AppEvent : public MTEvent {
    public:
        AppEvent(EventType type,
                long time, 
                flow_id flowId);
        ~AppEvent() override;
};

// are these necessary?
flow_id get_flow_id(event_t * event) {
    return event->flowId;
}

void set_flow_id(event_t * event, flow_id id) {
    event->flowId = id;
}

} // namespace ns3
#endif
