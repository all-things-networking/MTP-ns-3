#include "mt-queue.h"

namespace ns3 {
    template<typename event>
    queue_t<event>::queue_t(int lower_limit, int upper_limit, bool (*drop_policy) (event)): 
      upper_limit{upper_limit},
      lower_limit{lower_limit},
      drop_policy{drop_policy},
      appQueue(lower_limit, upper_limit, drop_policy),
      netQueue(lower_limit, upper_limit, drop_policy),
      progQueue(lower_limit, upper_limit, drop_policy),
      urgentQueue(lower_limit, upper_limit, drop_policy),
      timerQueue(lower_limit, upper_limit, drop_policy),
      memQueue(lower_limit, upper_limit, drop_policy)
      paused{false}
    {}

    template<typename event>
    bool queue_t<event>::empty() {
      return eventQueue.empty(); 
    }

    template<typename event>
    queue_t<event>::queue_t():
      upper_limit{100000},
      lower_limit{0},
      drop_policy{[](event e) { return false; }},
      paused{false}
    {}
  
    template<typename event>
    queue_t<event>::~queue_t() {
      while (!eventQueue.empty()) {
        event
        eventQueue.pop_front();
      }
    }

    template<typename event>
    void queue_t<event>::active() {
      return !(eventQueue.empty() || paused);
    }

    template<typename event>
    void queue_t<event>::push(event e) {
      // draft implementation

      // if queue is full, remove first event from beginning that satisfies drop policy
      if (eventQueue.size() > upper_limit) {
        for (auto it = eventQueue.begin(); it != eventQueue.end(); ++it) {
          if (drop_policy(*it)) {
            eventQueue.erase(it);
            break;
          }
        }
      } 
      
      // if queue is still full (i.e. drop policy didn't drop any packets), 
      //  then drop this packet
      if (eventQueue.size() > upper_limit) {
        return;
      }

      eventQueue.push(e);
    }

    template <typename event>
    event queue_t<event>::pop() {
      event retVal = eventQueue.front();
      eventQueue.pop_front();
      return retVal;
    }

    template <typename event>
    bool queue_t<event>::pause() {
      return paused = true;
    }

    template <typename event>
    bool queue_t<event>::unpause() {
      return paused = false;
    }

}