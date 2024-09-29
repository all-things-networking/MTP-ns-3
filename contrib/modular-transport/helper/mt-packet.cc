#include "mt-packet.h"
 
namespace ns3 {
  int pkt_t::len() { return GetSize(); }

  void pkt_t::add_data(Buffer newData) {
    // can't initialize a Packet with a Buffer object, instead need to pass in a uint8_t * and size
    int bufferSize = newData.GetSize();
    uint8_t * data = new uint8_t[bufferSize];
    newData.CopyData(data, bufferSize);
    Packet toAdd = Packet(data, bufferSize);
    AddAtEnd(Ptr<Packet>(&toAdd));
    // delete data array since the Packet constructor copies from it, so it's no longer needed
    delete[] data;
  }

  void pkt_t::add_data(uint8_t * newData, int size) {
    Packet toAdd = Packet(newData, size);
    AddAtEnd(Ptr<Packet>(&toAdd));
  }

  void pkt_t::get_data(uint8_t * outputBuffer, int bytesToCopy) { 
    CopyData(outputBuffer, bytesToCopy);
  }

  void pkt_t::add_hdr(MTHeader header) {
    AddHeader(header);
  }

  MTHeader pkt_t::extract_hdr() {
    MTHeader retval = MTHeader();
    RemoveHeader(retval);
    return retval;
  }
}

