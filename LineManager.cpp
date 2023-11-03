// Name: Viktoriia Kovinskaia
// Seneca Student ID: 110461217
// Seneca email: vkovinskaia@myseneca.ca
// Date of completion: November 29, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include "LineManager.h"

namespace sdds
{
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::fstream f(file);
        std::string str;
        Utilities u;
        
        if (!f.is_open() || file.empty()) {
            throw std::string("Can't open file");
        }
        while (!f.eof()) {
            getline(f, str);
            size_t position = 0;
            bool nextPos = true;
            std::string workstation = u.extractToken(str, position, nextPos);
            std::string next;
            if (nextPos) {
                next = u.extractToken(str, position, nextPos);
            }
            auto station = find_if(stations.begin(), stations.end(), [&](Workstation* w) {
                return w->getItemName().compare(workstation) == 0;
            });
            m_activeLine.push_back(*station);
            if (next.empty()) {
                m_activeLine.back()->setNextStation(nullptr);
            }
            else {
                for_each(stations.begin(), stations.end(), [&](Workstation* w) {
                    if (w->getItemName().compare(next) == 0) {
                        m_activeLine.back()->setNextStation(w);
                    }
                });
            }
        }
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* w) {
            auto firstStation = find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
                return ws->getNextStation() == w;
            });
            if (firstStation == m_activeLine.end()) {
                m_firstStation = w;
            }
        });
        m_cntCustomerOrder = g_pending.size();
        f.close();
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> reorderedSt;
        reorderedSt.push_back(m_firstStation);
        if (m_firstStation->getNextStation()) {
            reorderedSt.push_back(m_firstStation->getNextStation());
        }
        auto finish = m_activeLine.end() - 2;
        for_each(m_activeLine.begin(), finish, [&](Workstation* w) {
            reorderedSt.push_back(reorderedSt.back()->getNextStation());
        });
        m_activeLine = reorderedSt;
    }

    bool LineManager::run(std::ostream& os) {
        static int count = 0;
        bool flag;
        count++;
        os << "Line Manager Iteration: " << count << std::endl;
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* w) {
            w->fill(os);
        });
        for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* w) {
            w->attemptToMoveOrder();
        });
        if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
            flag = true;
        }
        else {
            flag = false;
        }
        return flag;
    }

    void LineManager::display(std::ostream& os) const {
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* w) {
            w->display(os);
        });
    }
}