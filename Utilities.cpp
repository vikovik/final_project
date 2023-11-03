// Name: Viktoriia Kovinskaia
// Seneca Student ID: 110461217
// Seneca email: vkovinskaia@myseneca.ca
// Date of completion: November 14, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define CRT_SECURE_NO_WARNINGS

#include "Utilities.h"

namespace sdds
{
    char Utilities::m_delimiter{};

    void Utilities::setFieldWidth(size_t newWidth){
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const{
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more){
        int delim;
        std::string token;
        if (str[next_pos] != m_delimiter){
            std::string temp = str.substr(next_pos);
            if ((delim = temp.find_first_of(m_delimiter)) == -1) {
                token = temp;
                trimSpaces(token);
                more = false;
            }
            else {
                token = temp.substr(0, delim);
                trimSpaces(token);
                next_pos += delim + 1;
                more = true;
            }
        }
        else{
            more = false;
            throw -1;
        }
        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }
        return token;
    }

    void Utilities::setDelimiter(char newDelimiter){
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter(){
        return m_delimiter;
    }

    void Utilities::trimSpaces(std::string& src) {
        if (src.length() > 0) {
            int begin = src.find_first_not_of(' ');
            int end = src.find_last_not_of(' ');
            if (begin == -1) {
                src = "";
            }
            else {
                src = src.substr(begin, end - begin + 1);
            }
        }
    }
}