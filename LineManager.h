// Name: Viktoriia Kovinskaia
// Seneca Student ID: 110461217
// Seneca email: vkovinskaia@myseneca.ca
// Date of completion: November 29, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Workstation.h"
#include "Utilities.h"

namespace sdds
{
    class LineManager {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation* m_firstStation = nullptr;
    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}
