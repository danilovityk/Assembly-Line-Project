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
    
    if(str.find(m_delimiter) != next_pos) {
        
        buffer = str.substr(next_pos, str.find(m_delimiter));
        buffer = buffer.substr(buffer.find_first_not_of(" "), buffer.find_last_not_of(" ") + 1);
        next_pos = str.find(m_delimiter) + 1;
        more = true;
        
        if(m_widthField < str.length()) {
            m_widthField = str.length();
        }
        
    }else {
        more = false;
        throw "this is retarded";
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



