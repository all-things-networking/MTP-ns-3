#ifndef UDP_RXAPP_H
#define UDP_RXAPP_H

#include "ns3/mt-rxapp.h"
#include "udp-event.h"
#include "udp-context.h"

namespace ns3 {
    class UDPRXAppParser : public MTRXAppParser {
        UDPContext * ctx;
        public:
            UDPRXAppParser(UDPContext * ctx) : ctx(ctx) {};
            virtual ~UDPRXAppParser();
            virtual event_t * request_parser(app_msg_t request, int flow_id) {
                // remark: in spec, request_parser is meant to extract values from the
                //  request to the RXAppParser-defined app_hdr class
                //  but here, request goes in the message and not the header
                pkt_t * pkt = new_pkt();

                auto now = std::chrono::system_clock::now();
                long timestamp = std::chrono::system_clock::to_time_t(now);
                return new SendEvent(timestamp, flow_id);
            }
    };
}

#endif