// Name: Viktoriia Kovinskaia
// Seneca Student ID: 110461217
// Seneca email: vkovinskaia@myseneca.ca
// Date of completion: November 14, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS

#include "Station.h"

namespace sdds
{
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string& str) {
        Utilities u;
        size_t position = 0;
        bool next = true;
        m_nameItem = u.extractToken(str, position, next);
        try {
            m_serialNumber = stoi(u.extractToken(str, position, next));
        }
        catch (std::invalid_argument& err){
            throw err;
        }
        try {
            m_numOfItems = stoi(u.extractToken(str, position, next));
        }
        catch (std::invalid_argument& err){
            throw err;
        }
        if (m_widthField < u.getFieldWidth()) {
            m_widthField = u.getFieldWidth();
        }
        m_description = u.extractToken(str, position, next);
        m_stationID = ++id_generator;
    }

    const std::string& Station::getItemName() const {
        return m_nameItem;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_numOfItems;
    }

    void Station::updateQuantity() {
        if (m_numOfItems > 0) {
            m_numOfItems--;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os.setf(std::ios::right);
        os.width(3);
        os.fill('0');
        os << m_stationID << " | ";
        os.unsetf(std::ios::right);
        os.setf(std::ios::left);
        os.width(m_widthField + 1);
        os.fill(' ');
        os << m_nameItem << " | ";
        os.unsetf(std::ios::left);
        os.setf(std::ios::right);
        os.width(6);
        os.fill('0');
        os << m_serialNumber << " | ";
        os.unsetf(std::ios::right);
        if (full) {
            os << std::setw(4) << std::setfill(' ');
            os.setf(std::ios::right);
            os << m_numOfItems << " | ";
            os.unsetf(std::ios::right);
            os << m_description;
        }
        os << std::endl;
    }
}
