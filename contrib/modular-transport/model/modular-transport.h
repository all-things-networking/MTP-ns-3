/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef MODULAR_TRANSPORT_H
#define MODULAR_TRANSPORT_H

#include "mt-rxapp.h"
#include "mt-txnet.h"
#include "mt-rxnet.h"
#include "mt-scheduler.h"
#include "mt-dispatcher.h"
#include "mt-context.h"
#include "../helper/mtp-types.h"
#include "mt-eventprocessor.h"
#include "ns3/ip-l4-protocol.h"
#include "ns3/ipv4-l3-protocol.h"
#include "ns3/node.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv6-address.h"
#include "ns3/sequence-number.h"

namespace ns3
{

class Node;

class ModularTransport: public IpL4Protocol
{
  public:
    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId();
    static const uint8_t PROT_NUMBER = 0xcc; //!< protocol number (0xcc)

    ModularTransport();
    ~ModularTransport() override;

    // Delete copy constructor and assignment operator to avoid misuse
    ModularTransport(const ModularTransport&) = delete;
    ModularTransport& operator=(const ModularTransport&) = delete;

    /**
     * Set node associated with this stack
     * \param node the node
     */
    void SetNode(Ptr<Node> node);

    void Start(
               const Ipv4Address& saddr,
               const Ipv4Address& daddr/*,
               MTContext* StartContext*/);

    void ReceiveAppMessage(const Ipv4Address& saddr,const Ipv4Address& daddr);
    void ReceiveNetPacket(const Ipv4Address& saddr,const Ipv4Address& daddr);
    /**
    main of simulation
    */
    void Mainloop();

     /**
     * \brief Send a packet
     *
     * \param pkt The packet to send
     * \param saddr The source Ipv4Address
     * \param daddr The destination Ipv4Address
     */
    void SendPacket(Ptr<Packet> pkt,
                    const Ipv4Address& saddr,
                    const Ipv4Address& daddr) const; 

    void HandleTimeout(MTEvent* ev);

    // From IpL4Protocol
    enum IpL4Protocol::RxStatus Receive(Ptr<Packet> p,
                                        const Ipv4Header& incomingIpHeader,
                                        Ptr<Ipv4Interface> incomingInterface) override;
    enum IpL4Protocol::RxStatus Receive(Ptr<Packet> p,
                                        const Ipv6Header& incomingIpHeader,
                                        Ptr<Ipv6Interface> incomingInterface) override;

    void ReceiveIcmp(Ipv4Address icmpSource,
                     uint8_t icmpTtl,
                     uint8_t icmpType,
                     uint8_t icmpCode,
                     uint32_t icmpInfo,
                     Ipv4Address payloadSource,
                     Ipv4Address payloadDestination,
                     const uint8_t payload[8]) override;
    
    void ReceiveIcmp(Ipv6Address icmpSource,
                     uint8_t icmpTtl,
                     uint8_t icmpType,
                     uint8_t icmpCode,
                     uint32_t icmpInfo,
                     Ipv6Address payloadSource,
                     Ipv6Address payloadDestination,
                     const uint8_t payload[8]) override;

    void SetDownTarget(IpL4Protocol::DownTargetCallback cb) override;
    void SetDownTarget6(IpL4Protocol::DownTargetCallback6 cb) override;
    int GetProtocolNumber() const override;
    IpL4Protocol::DownTargetCallback GetDownTarget() const override;
    IpL4Protocol::DownTargetCallback6 GetDownTarget6() const override;

    virtual MTContext* InitContext(flow_id fid){return NULL;}

    virtual void print_debugging_info(flow_id fid){}
  protected:
    void DoDispose() override;

    /**
     * \brief Setup callbacks when aggregated to a node
     *
     * This function will notify other components connected to the node that a
     * new stack member is now connected. This will be used to notify Layer 3
     * protocol of layer 4 protocol stack to connect them together.
     * The aggregation is completed by setting the node in the transport layer,
     * linking it to the ipv4 or ipv6 and setting up other relevant state.
     */
    void NotifyNewAggregate() override;
    MTRXAppParser* rxapp;
    MTTXNetScheduler* txnet;
    MTRXNetParser* rxnet;
    MTScheduler* scheduler;
    MTDispatcher* dispatcher;
    MTIntermediateOutput* interm_output;
    flow_map<MTContext*> ctx_table;
    bool drop_policy(MTEvent * event);
    int lower_limit = 0, upper_limit = 10000; // for queue_t in scheduler types

  private:
    // MTDispatcher* dispatcher;
    // MTReceiver* receiver;
    Ptr<Node> m_node;                                //!< the node this stack is associated with
    IpL4Protocol::DownTargetCallback m_downTarget;   //!< Callback to send packets over IPv4
    IpL4Protocol::DownTargetCallback6 m_downTarget6; //!< Callback to send packets over IPv6
};

} // namespace ns3

#endif /* MODULAR_TRANSPORT_H */