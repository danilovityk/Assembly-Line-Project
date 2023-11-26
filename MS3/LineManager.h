// - Danylo Vityk
// - 176326213
// - dvityk@myseneca.ca
// - Nov 23, 2023

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include "Workstation.h"
namespace sdds {

class LineManager{
    std::vector<Workstation*> m_activeLine;
    size_t m_cntCustomerOrder;
    Workstation* m_firstStation;
    
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    void reorderStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};

}

#endif /* LineManager_hpp */
