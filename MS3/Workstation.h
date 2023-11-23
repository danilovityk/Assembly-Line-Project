#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds{

class Workstation : public Station{
    std::deque<CustomerOrder> m_orders;
    Workstation* m_nextWorkStation = nullptr;
public:
    Workstation(const std::string&);
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* station = nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
    Workstation(const Workstation&) = delete;
    Workstation(Workstation&&) = delete;
    Workstation& operator=(const Workstation&) = delete;
    Workstation& operator=(Workstation&&) = delete;
    
};

extern std::deque<CustomerOrder> g_pending;
extern std::deque<CustomerOrder> g_completed;
extern std::deque<CustomerOrder> g_incomplete;


}

#endif /* Workstation_hpp */
