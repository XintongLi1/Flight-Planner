#ifndef _FLIGHT_H_
#define _FLIGHT_H_
#include "flightnameexception.h"
#include "flightplanner.h"
#include "flightplan.h"
#include <memory>
#include <string>

class Flight{ // flight : graphNode, flightPlanner : graph
    std::string from, to;
    int duration, price;
    std::string name;

    public:
        Flight(const std::string & f, const std::string & t, int d, int p, const std::string & n); // cannot have std::shared_ptr<Airport> here, because of cyclical reference
        std::string getFrom();
        std::string getTo();
        int getDuration();
        int getPrice();
        std::string getName();
};



#endif
