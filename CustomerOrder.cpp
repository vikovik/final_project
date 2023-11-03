// Name: Viktoriia Kovinskaia
// Seneca Student ID: 110461217
// Seneca email: vkovinskaia@myseneca.ca
// Date of completion: November 22, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include "CustomerOrder.h"

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {}

	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities u;
		size_t position = 0;
		bool next = true;

		m_name = u.extractToken(str, position, next);
		m_product = u.extractToken(str, position, next);
		m_cntItem = 0;
		size_t begin = position;
		while (next) {
			u.extractToken(str, position, next);
			m_cntItem++;
		}
		m_lstItem = new Item * [m_cntItem];
		next = true;
		for (size_t i = 0u; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(u.extractToken(str, begin, next));
		}
		if (m_widthField < u.getFieldWidth()) {
			m_widthField = u.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& order) {
		throw std::string("ERROR: Cannot make copies.");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept {
		*this = std::move(order);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept {
		if (this != &order) {
			for (size_t i = 0u; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[]m_lstItem;
			m_name = order.m_name;
			m_product = order.m_product;
			m_cntItem = order.m_cntItem;
			m_lstItem = order.m_lstItem;
			order.m_name = {};
			order.m_product = {};
			order.m_cntItem = 0;
			order.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isOrderFilled() const {
		bool filled = true;
		for (size_t i = 0u; i < m_cntItem && filled; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				filled = false;
			}
		}
		return filled;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool filled = true;
		for (size_t i = 0u; i < m_cntItem && filled; i++) {
			if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false) {
				filled = false;
			}
		}
		return filled;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (m_lstItem[i]->m_isFilled == false && station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", "
						<< m_product << " ["
						<< m_lstItem[i]->m_itemName << "]"
						<< std::endl;
					break;
				}
				else if (station.getQuantity() == 0) {
					os << "    Unable to fill " << m_name << ", "
						<< m_product << " ["
						<< m_lstItem[i]->m_itemName << "]"
						<< std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0u; i < m_cntItem; i++) {
			os << "[";
			os.setf(std::ios::right);
			os.width(6);
			os.fill('0');
			os << m_lstItem[i]->m_serialNumber << "] ";
			os.unsetf(std::ios::right);
			os.setf(std::ios::left);
			os.width(m_widthField);
			os.fill(' ');
			os << m_lstItem[i]->m_itemName << "   - ";
			os.unsetf(std::ios::left);
			if (m_lstItem[i]->m_isFilled == false) {
				os << "TO BE FILLED" << std::endl;
			}
			else {
				os << "FILLED" << std::endl;
			}
		}
	}
}