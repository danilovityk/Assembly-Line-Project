// - Danylo Vityk
// - 176326213
// - dvityk@myseneca.ca
// - Nov 6, 2023

#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;

Station::Station(const std::string& str) {

    Utilities util;
    m_id = int(++id_generator);
    size_t nextpos = 0;
    bool more = false;
    string buffer = "";
    
   
    
    try{
        m_name = util.extractToken(str, nextpos, more);
        buffer = util.extractToken(str, nextpos, more);
        m_serialNum = stoul(buffer);
        buffer = util.extractToken(str, nextpos, more);
        m_stockNum = stoul(buffer);
        if (util.getFieldWidth() > m_widthField){
            m_widthField = util.getFieldWidth();
        }
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
    if (m_stockNum-1 >= 0){ --m_stockNum; }
}

void Station::display(std::ostream &os, bool full) const {
    os << setw(3) << setfill('0') <<  m_id 
    << setfill(' ') << " | "
    << setw(int(m_widthField)) << left << m_name << right
    << " | " << setw(6) << setfill('0')
    << m_serialNum << setfill(' ') << " | ";
    
    if (full) {
        os << setw(4) << m_stockNum << " | " << m_desc;
    }
    
    os << endl;
}




}



