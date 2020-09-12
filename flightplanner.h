#ifndef _FLIGHTPLANNER_H_
#define _FLIGHTPLANNER_H_
#include "airport.h"

class FlightPlan;

class FlightPlanner{
    std::map<std::string, std::shared_ptr<Airport>> graph;
    std::vector<std::vector<std::shared_ptr<Flight>>> planTripHelper (const std::string & from, const std::string &to);
    public:
        FlightPlanner();
        void addAirport(const std::string & name); // adds an airport to the graph. FlightNameException is thrown if an airport already exists with the given name
        void addFlight(const std::string &from, const std::string &to, int duration, int price, const std::string &name);
        std::vector<std::shared_ptr<FlightPlan>> planTrip (const std::string & from, const std::string &to);
};

#endif
