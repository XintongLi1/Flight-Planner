// Created Time: Sat 25 Jul 2020 12:56:07 PM EDT
#include "flightplanner.h"
#include "flightnameexception.h"
#include "flight.h"
#include "flightplan.h"
#include <algorithm>
using namespace std;

FlightPlanner::FlightPlanner(){}

void FlightPlanner::addAirport(const std::string & name) // adds an airport to the graph. FlightNameException is thrown if an airport already exists with the given name
{
    if (graph.count(name) == 1)
            throw FlightNameException();
    else{
        shared_ptr<Airport> airport = make_shared<Airport>(Airport{name});
        graph.emplace(name, airport);
    }
}

void FlightPlanner::addFlight(const std::string &from, const std::string &to, int duration, int price, const std::string &name){
    if (graph.count(from) == 1 && graph.count(to) == 1){
        for (auto & p : graph){
            for (auto & f : p.second->flights){
                if (f->getName() == name) throw FlightNameException();
            }
        }
        graph[from]->flights.emplace_back(make_shared<Flight>(Flight(from, to, duration, price, name)));
        graph[to]->flights.emplace_back(make_shared<Flight>(Flight(to, from, duration, price, name)));
    }
    else throw FlightNameException();
  
}

std::vector<std::shared_ptr<FlightPlan>> FlightPlanner::planTrip (const std::string & from, const std::string &to){
    if (graph.count(from) == 0 || graph.count(to) == 0) throw FlightNameException();
    vector<shared_ptr<FlightPlan>> res;
    vector<vector<shared_ptr<Flight>>> build;
    for (auto & a : graph[from]->flights){
        if (to == a->getTo()){
            vector<shared_ptr<Flight>> tmp;
            tmp.emplace_back(a);
            build.emplace_back(tmp);
        }
        else{
            graph[from]->visitied = 1;
            vector<vector<shared_ptr<Flight>>> tmp = planTripHelper(a->getTo(), to);        
            if (!tmp.empty()){
                for_each(tmp.begin(), tmp.end(), [a](vector<shared_ptr<Flight>> & fl){fl.push_back(a); return fl;});
                for (auto & r : tmp){
                    reverse(r.begin(), r.end());
                    build.emplace_back(r);
                }
            }
            graph[from]->visitied = 0;
        }
        
    }
    if (!build.empty()){
        for (auto & r : build){
            auto plan = make_shared<FlightPlan>(FlightPlan{r});
            res.emplace_back(plan);
        }
    }
    sort(res.begin(), res.end(), [](shared_ptr<FlightPlan> l, shared_ptr<FlightPlan> r ){ return l->getPain() < r->getPain(); });
    return res;
}



vector<std::vector<std::shared_ptr<Flight>>> FlightPlanner::planTripHelper (const std::string & from, const std::string &to){
    vector<vector<shared_ptr<Flight>>> res;        
    for (auto & a : graph[from]->flights){
        if (to == a->getTo() && graph[to]->visitied == 0){
            vector<shared_ptr<Flight>> restmp;
            restmp.emplace_back(a);
            res.emplace_back(restmp);
        }
        else{
            if (graph[a->getTo()]->visitied == 0){
                graph[from]->visitied = 1;
                vector<vector<shared_ptr<Flight>>> build = planTripHelper(a->getTo(), to);        
                if (!build.empty()){
                    for_each(build.begin(), build.end(), [a](vector<shared_ptr<Flight>> & fl){fl.push_back(a); return fl;});
                    for (auto & r : build){
                        res.emplace_back(r);
                    }
                }
                graph[from]->visitied = 0;
            }
        }
        
    }
    return res;
}


