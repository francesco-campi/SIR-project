#ifndef PERSON_H
#define PERSON_H

#include "InfectionStatus.hpp"

#include <utility>

struct Person
{
    InfectionStatus infection_status;
    // (x , y) coordinates of the position of the person
    std::pair<double, double> position;
    // counts how many time steps the person has been infected
    int counter_infected;
    //counts for how many steps the person has been recovered, after that becomes susceptible again
    int counter_recovered;
    //the direction where the Person is walking to
    double direction;
    // (x , y) coordinates of the old position of the person before going to the meeting point
    std::pair<double, double> old_position;
    // if the person is in the meeting point
    bool at_meeting_point;

};

#endif
