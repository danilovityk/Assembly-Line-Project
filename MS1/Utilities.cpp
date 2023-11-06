// - Danylo Vityk
// - 176326213
// - dvityk@myseneca.ca
// - Nov 6, 2023

#include <string>
#include "Utilities.h"

namespace sdds {

char Utilities::m_delimiter = '0';

void Utilities::setFieldWidth(size_t newWidth) {
    m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const {
    return m_widthField;
}

std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more) {
    std::string buffer{};
    if(str.find(m_delimiter, next_pos) != std::string::npos) {
        
        if(str.find(m_delimiter, next_pos) == next_pos) {
            more = false;
            throw "this is retarded";
        }
        
        buffer = str.substr(next_pos, str.substr(next_pos).find_first_of(m_delimiter));
        buffer = buffer.substr(buffer.find_first_not_of(" "), buffer.find_last_not_of(" ") + 1);
        next_pos = str.find(m_delimiter, next_pos) + 1;
        more = true;
        
        if(m_widthField < buffer.length()) {
            m_widthField = buffer.length();
        }

            
    }else {
        
        buffer = str.substr(next_pos, str.substr(next_pos).find_first_of(m_delimiter));
        buffer = buffer.substr(buffer.find_first_not_of(" "), buffer.find_last_not_of(" ") + 1);
        next_pos = str.find(m_delimiter, next_pos) + 1;
        more = false;
        
        if(m_widthField < buffer.length()) {
            m_widthField = buffer.length();
        }
       
    }
    return buffer;
}

void Utilities::setDelimiter(char newDelimiter) {
    m_delimiter = newDelimiter;
}

char Utilities::getDelimiter() {
    return m_delimiter;
}


}



