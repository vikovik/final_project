// Name: Viktoriia Kovinskaia
// Seneca Student ID: 110461217
// Seneca email: vkovinskaia@myseneca.ca
// Date of completion: November 14, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include "Utilities.h"

namespace sdds
{
    class Station {
        int m_stationID{};
        std::string m_nameItem{};
        std::string m_description{};
        size_t m_serialNumber{};
        size_t m_numOfItems{};
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station(const std::string& str);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}

