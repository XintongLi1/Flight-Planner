#ifndef _FLIGHTPLAN_H_
#define _FLIGHTPLAN_H_
#include "airport.h"
class Flight;

class FlightPlan{
    std::vector<std::shared_ptr<Flight>> plan; 
    public:
        FlightPlan(const std::vector<std::shared_ptr<Flight>> & = {});
        std::vector<std::shared_ptr<Flight>> getSteps();
        int getDuration();
        int getPrice();
        int getPain(); // 1.2^d * p

};


#endif
