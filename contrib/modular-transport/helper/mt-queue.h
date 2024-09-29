#ifndef MT_QUEUE_H
#define MT_QUEUE_H

#include <type-traits.h> // static_assert

#include <deque>
#include "mtp-types.h"

namespace ns3 {
  template<typename event>
  class queue_t {
    // static_assert to ensure that queue event type is derived from MTEvent
    static_assert(std::is_base_of<MTEvent, event>::value, "queue_t type must be derived from MTEvent");

    std::deque<event> eventQueue;
    int upper_limit;
    int lower_limit;
    bool (*drop_policy) (event);
    bool paused;

    public:
      queue_t();
      queue_t(int lower_limit, int upper_limit, bool (*drop_policy) (event));
      ~queue_t();
      bool pause();
      bool unpause();
      void active();
      void push(event e);
      bool empty();
      event pop();
  };

}

#endif