#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "CustomerOrder.h"
using namespace std;
namespace sdds {

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {
    m_name = "";
    m_product = "";
    m_cntItem = 0;
    m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(const std::string & str) {
    Utilities util;
    
    size_t nextpos = 0;
    bool more = false;
    string buffer = "";
    
    
    
    try{
        m_name = util.extractToken(str, nextpos, more);
        m_product = util.extractToken(str, nextpos, more);
        while (more){
            buffer = util.extractToken(str, nextpos, more);
            
            Item** tempArr = new Item*[m_cntItem + 1];
        
            for (size_t i = 0; i < m_cntItem; i++){
                tempArr[i] = new Item(*m_lstItem[i]);
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            
            tempArr[m_cntItem++] = new Item (buffer);
            m_lstItem = tempArr;
            
        }
        if (util.getFieldWidth() > m_widthField){
            m_widthField = util.getFieldWidth();
        }
    }catch(const char*){
        cerr << "failed the extraction of a token";
    }
    
}

CustomerOrder::CustomerOrder(const CustomerOrder &) {
    throw "Copy construction is not allowed";
}

CustomerOrder::CustomerOrder(CustomerOrder && source) noexcept {
    *this = std::move(source);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder && source) noexcept{
    if(this != &source){
        for (size_t i = 0; i < m_cntItem; i++){
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_cntItem = source.m_cntItem;
        m_name = source.m_name;
        m_product = source.m_product;
        m_lstItem = source.m_lstItem;
         
        source.m_cntItem = 0;
        source.m_lstItem = nullptr;
        
    }
    
    return *this;
}

CustomerOrder::~CustomerOrder() {
    for (size_t i = 0; i < m_cntItem; i++){
        delete m_lstItem[i];
    }
    delete[] m_lstItem;
}

bool CustomerOrder::isOrderFilled() const {
    bool result = false;
    for(size_t i = 0; i < m_cntItem; i++){
            if(!m_lstItem[i]->m_isFilled){
                i = m_cntItem;
                result = false;
            }else{
                result = true;
            }
    }
    
    return result;
}

bool CustomerOrder::isItemFilled(const std::string &itemName) const {
    bool result = true;
    for(size_t i = 0; i < m_cntItem; i++){
        if(m_lstItem[i]->m_itemName == itemName){
            if(!m_lstItem[i]->m_isFilled){
                i = m_cntItem;
                result = false;
            }else{
                result = true;
            }
        }
    }
    
    return result;
}

void CustomerOrder::fillItem(Station &station, std::ostream &os) {
    for(size_t i = 0; i < m_cntItem; i++){
        if(m_lstItem[i]->m_itemName == station.getItemName()){
            if(station.getQuantity() > 0){
                station.updateQuantity();
                m_lstItem[i]->m_isFilled = true;
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                os << "    Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << endl;
            }else{
                os << "    Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << endl;
            }
            
        }
    }
}

void CustomerOrder::display(std::ostream &os) const {
    os << m_name << " - " << m_product << endl;
    
    for(size_t i = 0; i < m_cntItem; i++){
        os << "[" << setw(6) << setfill('0') << left << m_lstItem[i]->m_serialNumber << "]" << setfill(' ')
        << " " << setw(int(m_widthField)) << m_lstItem[i]->m_itemName << " - ";
        if(isItemFilled(m_lstItem[i]->m_itemName)){
            os << "FILLED";
        }else{
            os << "TO BE FILLED";
        }
        os << endl;
    }
   
}





}



