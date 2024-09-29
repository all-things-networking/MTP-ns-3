#include "mt-dispatcher.h"

namespace ns3 {
  // still need to provide a definition for the pure virtual destructor
  inline MTDispatcher::~MTDispatcher() {}

  std::unordered_map<std::string, std::vector<MTEventProcessor*>> MTDispatcher::getEventMap() {
    return eventMap;
  }

} // namespace ns3