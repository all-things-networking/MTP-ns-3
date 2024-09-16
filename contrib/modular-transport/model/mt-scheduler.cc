#include "mt-scheduler.h"
#include <iostream>

namespace ns3 {
  queue_set::queue_set() {
    total_queues = 6;
  }

  MTScheduler::MTScheduler() {
    flowMap = flow_map<queue_set>();
    eventSelector = flow_map<unsigned int>(0);
    flowSelector = 0;
  }

  void MTScheduler::enqueue_event(flow_id id, MTEvent * event) {
    flowMap[id].enqueue_event(event);
    //std::cout <<"added event of type "<<event->subtype<<" for flow "<<event->flowId<< std::endl;
  }

  flow_id MTScheduler::next_flow() {
    auto it = flowMap.begin();
    for (unsigned int i = 0; i < flowSelector; i++) {
      it++;
    }
    flowSelector=(flowSelector+1)%flowMap.size();
    return it->first;
  }

  MTEvent * MTScheduler::next_event(flow_id id) {
    queue_set flowQueueSet = flowMap[id];
    unsigned int selector=0;
    do{
      selector = eventSelector[id]++ % flowQueueSet.total_queues;
    }while(flowQueueSet.get_queue(selector).empty());
    MTEvent* ev = flowQueueSet.get_queue(selector).front();
    flowMap[id].pop_queue(selector);
    return ev;
  }

  MTEvent * MTScheduler::get_next_event() {
    //std::cout <<"Looking for next event"<< std::endl;
    flow_id id;
    do{
      id = this->next_flow();
      //std::cout <<"Looking at flow id "<<id<< std::endl;
    }while(flowMap[id].is_empty());
    //std::cout <<"found an event at flow_id "<<id<< std::endl;
    MTEvent * event = this->next_event(id);
    return event;
  }

  bool MTScheduler::is_empty(){
    std::cout <<"Scheduler: Checking For Pending Events."<< std::endl;
    for (auto it = flowMap.begin(); it != flowMap.end(); it++) {
      if(!it->second.is_empty()){
        //std::cout <<"found non empty event_queue for flow "<<it->first<< std::endl;
        return false;
      }
    }
    std::cout <<"Scheduler: No Pending Events"<< std::endl;
    return true;
  }

  void queue_set::enqueue_event(MTEvent * event) {
    switch (event->subtype) {
      case APP_EVENT:
        appQueue.push(event);
        break;
      case NET_EVENT:
        netQueue.push(event);
        break;
      case PROG_EVENT:
        progQueue.push(event);
        break;
      case URGENT_EVENT:
        urgentQueue.push(event);
        break;
      case TIMER_EVENT:
        timerQueue.push(event);
        break;
      case MEM_EVENT:
        memQueue.push(event);
        break;
    }
  }

  bool queue_set::is_empty() {
    bool isEmpty=appQueue.empty()&&netQueue.empty()&&progQueue.empty()&&urgentQueue.empty()&&timerQueue.empty()&&memQueue.empty();
    return isEmpty;
  }

  std::queue<MTEvent *> queue_set::get_queue(int selector){
    switch (selector) {
      case APP_EVENT:
        return appQueue;
        break;
      case NET_EVENT:
        return netQueue;
        break;
      case PROG_EVENT:
        return progQueue;
        break;
      case URGENT_EVENT:
        return urgentQueue;
        break;
      case TIMER_EVENT:
        return timerQueue;
        break;
      case MEM_EVENT:
        return memQueue;
        break;
    }
  }

  void queue_set::pop_queue(int selector){
    switch (selector) {
      case APP_EVENT:
        appQueue.pop();
        break;
      case NET_EVENT:
        netQueue.pop();
        break;
      case PROG_EVENT:
        progQueue.pop();
        break;
      case URGENT_EVENT:
        urgentQueue.pop();
        break;
      case TIMER_EVENT:
        timerQueue.pop();
        break;
      case MEM_EVENT:
        memQueue.pop();
        break;
    }
  }

}

