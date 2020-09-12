// Created Time: Sat 25 Jul 2020 11:41:15 AM EDT
#include "flight.h"
#include <memory>

using namespace std;


Flight::Flight(const std::string & f, const std::string & t, int d, int p, const std::string & n)
    : from{f}, to{t}, duration{d}, price{p}, name{n}{}
        
std::string Flight::getFrom(){
    return from;
}

std::string Flight::getTo(){
    return to;
}

int Flight::getDuration(){
    return duration;
}

int Flight::getPrice(){
    return price;
}

std::string Flight::getName(){
    return name;
}
