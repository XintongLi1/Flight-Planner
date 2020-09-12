// Created Time: Sat 25 Jul 2020 12:06:30 PM EDT
#include "flightplan.h"
#include "flight.h"
#include <cmath>
using namespace std;


FlightPlan::FlightPlan(const vector<std::shared_ptr<Flight>> & p): plan{p}{}

std::vector<std::shared_ptr<Flight>> FlightPlan::getSteps(){
    return plan;
}

int FlightPlan::getDuration(){
    int dt = 0;
    for (auto & f : plan){
        dt += f->getDuration(); 
    }
    return dt + (plan.size() - 1);
}

int FlightPlan::getPrice(){
    int p = 0;
    for (auto & f : plan){
        p += f->getPrice(); 
    }
    return p;
}

int FlightPlan::getPain(){
    return pow(1.2, getDuration()) * getPrice();
}

