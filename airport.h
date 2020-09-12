#ifndef _AIRPOTR_H_
#define _AIRPOTR_H_
#include <string>
#include <map>
#include <memory>
#include <vector>

class Flight;

struct Airport{
    std::string name;
    std::vector<std::shared_ptr<Flight>> flights;
    bool visitied;
    Airport(const std::string & name);
};

#endif
