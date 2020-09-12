#include <iostream>
#include <memory>

#include "flight.h"

int main()
{
    // Memory testing mode
    bool memoryTestMode = false;

    // The current command
    char command;

    // Arguments to the current command
    std::string from, to, name;
    int duration, price;

    // Used to count the flight plan number
    int num;

    // Our flight planner itself, as a shared_ptr
    auto flightPlanner = std::make_shared<FlightPlanner>();

    // Plans returned by planTrip
    std::vector<std::shared_ptr<FlightPlan>> plans;

    while (true) {
        std::cin >> command;

        // Quit if requested
        if (std::cin.fail() || command == 'q') break;

        // Perform the command
        switch (command) {
            case 'a':
                // a <name>
                // Adds an airport
                std::cin >> name;
                try {
                    flightPlanner->addAirport(name);
                } catch (FlightNameException &fne) {
                    std::cout << "An airport with that name already exists!" << std::endl;
                }
                break;

            case 'f':
                // f <from> <to> <duration> <price> <name>
                // Adds a flight
                std::cin >> from >> to >> duration >> price >> name;
                try {
                    flightPlanner->addFlight(from, to, duration, price, name);
                } catch (FlightNameException &fne) {
                    std::cout << "A flight with that name already exists!" << std::endl;
                }
                break;

            case 'p':
                // p <from> <to>
                // Plans a trip
                std::cin >> from >> to;
                try {
                    plans = flightPlanner->planTrip(from, to);
                } catch (FlightNameException &fne) {
                    std::cout << "One of those airports does not exist!" << std::endl;
                    break;
                }

                // Possibly delete our flight planner
                if (memoryTestMode) {
                    /* Deliberately forget the flight planner, to make sure
                     * memory is neither leaked nor lost. */
                    flightPlanner = std::make_shared<FlightPlanner>();
                }

                // Output all the plans
                num = 1;
                for (auto plan : plans) {
                    // Overall details
                    std::cout << "Flight plan " << (num++) << ":" << std::endl
                              << "\tDuration:\t" << plan->getDuration() << " hours" << std::endl
                              << "\t   Price:\t$" << plan->getPrice() << std::endl
                              << "\t    Pain:\t" << plan->getPain() << std::endl
                              << "\t Details:" << std::endl;

                    // And steps
                    for (auto flight : plan->getSteps()) {
                        std::cout << "\t\t" << flight->getFrom() << "->" << flight->getTo() << std::endl
                                  << "\t\t\tFlight " << flight->getName() << ", "
                                  << flight->getDuration() << " hours, $"
                                  << flight->getPrice() << std::endl;
                    }
                }
                break;

            case 'm':
                // m
                // Enables/Disables memory test mode
                memoryTestMode = !memoryTestMode;
                std::cout << "Memory test mode " << (memoryTestMode ? "enabled." : "disabled.") << std::endl;
                break;

            default:
                std::cout << "Unrecognized command!" << std::endl;
        }
    }

    return 0;
}
