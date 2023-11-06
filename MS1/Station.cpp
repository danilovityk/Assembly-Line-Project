#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

Station::Station(const std::string & str) {
    Utilities util;
    size_t nextpos = 0;
    bool more = false;
    string buffer = "";
    
    if (util.getFieldWidth() > m_widthField){
        m_widthField = util.getFieldWidth();
    }
    
    try{
        m_name = util.extractToken(str, nextpos, more);
        buffer = util.extractToken(str, nextpos, more);
        m_serialNum = stoul(buffer);
        buffer = util.extractToken(str, nextpos, more);
        m_stockNum = stoul(buffer);
        m_desc = util.extractToken(str, nextpos, more);
    }catch(const char*){
        cerr << "failed the extraction of a token";
    }
    
    
    
}

const std::string &Station::getItemName() const {
    return m_name;
}

size_t Station::getNextSerialNumber() {
    return m_serialNum++;
}

size_t Station::getQuantity() const {
    return m_stockNum;
}

void Station::updateQuantity() {
    if (m_stockNum-1 > 0){ --m_stockNum; }
}

void Station::display(std::ostream &os, bool full) const {
    os << setw(3) << m_id << "|" << setw(int(m_widthField)) << m_name << "|" << setw(6) << m_serialNum << "|";
    
    if (full) {
        os << setw(4) << m_stockNum << "|" << m_desc;
    }
    
    os << endl;
}




}



