// - Danylo Vityk
// - 176326213
// - dvityk@myseneca.ca
// - Nov 23, 2023

#include <fstream>
#include <string>
#include <algorithm>
#include <iostream> //debugging purposes only
#include <vector>
#include "LineManager.h"
using namespace std;
namespace sdds{
    
LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) {
    fstream filep(file);
    if(filep.is_open()){
        string buffer;
        while(getline(filep, buffer)){
            if(buffer.find('|') != std::string::npos){
                size_t delim = buffer.find('|');
                string stationName, nextName;
                stationName = buffer.substr(0, delim);
                nextName = buffer.substr(delim + 1);
                
                auto it = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station){
                    return station->getItemName() == stationName;
                });
                
                if (it != stations.end()) {
                    m_activeLine.push_back(*it);
                }else{
                    cerr << "STATION NOT FOUND" << endl;
                }
                
                auto nextIt = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station){
                    return station->getItemName() == nextName;
                });
                
                if (it != stations.end()) {
                    m_activeLine.back()->setNextStation(*nextIt);
                }else{
                    cerr << "STATION NOT FOUND (Next)" << endl;
                }
                
            }else{
                
                auto it = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station){
                    return station->getItemName() == buffer;
                });
                
                if (it != stations.end()) {
                    m_activeLine.push_back(*it);
                }else{
                    cerr << "STATION NOT FOUND (No next)" << endl;
                }
            }
            
            auto first = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                return std::none_of(stations.begin(), stations.end(), [&](Workstation* other) {
                    return other != station && other->getNextStation() == station;
                });
            });
            
            if (first != stations.end()) {
                m_firstStation = *first;
            }else{
                cerr << "STATION NOT FOUND (No next)" << endl;
            }
            
            m_cntCustomerOrder = g_pending.size();
           
        }
    }else{
        throw "File cannot be opened";
    }
}

void LineManager::reorderStations() {
    std::sort(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* first, Workstation* second) {
        unsigned dist1 = 0, dist2 = 0;
        Workstation* currentStation = m_firstStation;

        while (currentStation != first) {
            currentStation = currentStation->getNextStation();
            ++dist1;
        }
        currentStation = m_firstStation;

        while (currentStation != second) {
            currentStation = currentStation->getNextStation();
            ++dist2;
        }
        return dist1 < dist2;
    });
}

bool LineManager::run(std::ostream &os) {
    static size_t counter = 0;
    ++counter;
    bool result = true;
    os << "Line Manager Iteration: " << counter << endl;
    if(g_pending.size() > 0){
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }
    for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
        station->fill(os);
        
    });
    
    for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
        station->attemptToMoveOrder();
    });
    
    
    if(g_completed.size() + g_incomplete.size() == m_cntCustomerOrder){
        result = true;
    }else{
        result = false;
    }
    
    
    return result;
}

void LineManager::display(std::ostream &os) const {
    for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* station){
        station->display(os);
    });
}


}

