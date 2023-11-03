// Name: Viktoriia Kovinskaia
// Seneca Student ID: 110461217
// Seneca email: vkovinskaia@myseneca.ca
// Date of completion: November 29, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <deque>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds
{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{};
    public:
        Workstation(const std::string& src);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
        Workstation(const Workstation& src) = delete;
        Workstation& operator=(const Workstation& src) = delete;
        Workstation(Workstation&& src) = delete;
        Workstation& operator=(Workstation&& src) = delete;
    };
}
