#include <cmath> //sin, cos
#define _USE_MATH_DEFINES
#include <random>
#include <vector>
#include "../include/Person.hpp"
#include "../include/InfectionStatus.hpp"
#include "../include/Population.hpp"
#include <iostream>

Population::Population(std::pair<double, double> bounding_box, double infection_radius,
                       double infection_probability, int num_steps, double step_size, int recovery_time, int susceptibility_time,
                       int population_size, bool add_meetingpoint, double meetingpoint_probability) :
                                              bounding_box(bounding_box),
                                              infection_radius(infection_radius),
                                              infection_probability(infection_probability),
                                              num_steps(num_steps),
                                              recovery_time(recovery_time),
                                              susceptibility_time(susceptibility_time),
                                              step_size(step_size),
                                              population_size(population_size),
                                              add_meetingpoint(add_meetingpoint),
                                              meetingpoint_probability(meetingpoint_probability)
{
    std::pair<double, double> position;

    people.reserve(population_size);
    for (int i = 0; i < population_size; i++)
    {
        // calculate random position in bounding box
        position = {unif_width(re), unif_height(re)};
        //calculate random direction of the walk inside of the bounding box
        double direction = unif_angle(re);
        if (i == 0)
        {
            people.push_back({InfectionStatus::infected, position, 0, 0, direction, position, false});
        }
        else
        {
            people.push_back({InfectionStatus::susceptible, position, 0, 0, direction, position, false});
        }
    }
    // calculate random position in bounding box for the meeting_point
    meeting_point = {bounding_box.first * 0.5, bounding_box.second * 0.5};
}

void Population::compute_position(Person& person){
    //get old positions
    double pos_x = person.position.first;
    double pos_y = person.position.second;
    double new_pos_x, new_pos_y;
           
    double direction = person.direction ;
    //update positions
    new_pos_x = pos_x + step_size * std::cos(direction);
    new_pos_y = pos_y + step_size * std::sin(direction);
    //if the new position extends the bounding box, 
    //then let the person bounce at the boundary
    if(new_pos_x > bounding_box.first ){
        new_pos_x = bounding_box.first - (new_pos_x - bounding_box.first);
        direction = M_PI - direction;
    }
    else if(new_pos_x < 0 ){
        new_pos_x = -1 * new_pos_x;
        direction = M_PI - direction;
    }

    if(new_pos_y > bounding_box.second){
        new_pos_y = bounding_box.second - (new_pos_y - bounding_box.second);
        direction =  -1 * direction;
    }
    else if(new_pos_y < 0){
        new_pos_y = -1 * new_pos_y;
        direction =  -1 * direction;
    }
    //update position
    person.position = {new_pos_x, new_pos_y};
    person.direction = direction;
            

}

// changes the positions of each person by a random step of fixed length and
// deals with the box dimension
void Population::update_positions()
{

    for (auto &person : people)
    {   
        double p = probability(re);
        //the probability for p to be smaller than 0.05 is exactly the probability 0.05
        //since p comes from a uniform distribution from 0 to 1
        if(add_meetingpoint == true){
            if (p <= 0.05 && person.at_meeting_point == false ){
            person.old_position = person.position;
            person.position = meeting_point;
            person.at_meeting_point = true;
            }
            else if(person.at_meeting_point == true ){
                person.position = person.old_position;
                person.at_meeting_point = false;
            }
            else{
                compute_position(person);
            }
        }
        else{
            compute_position(person);
        }   
    }
}

// checks for neighbours of infected people and changes the status with
// probability infection_probability
void Population::update_infected()
{
    //first extract all infected people
    std::vector<int> infected_positions, susceptible_positions;
    for (int i = 0; i < population_size; i++)
    {
        if (people[i].infection_status == InfectionStatus::infected)
        {
            infected_positions.push_back(i);
        }
        else if (people[i].infection_status == InfectionStatus::susceptible)
        {
            susceptible_positions.push_back(i);
        }
    }

    //Now check for the neighbours of all the infected people
    //change the status of a neighbour with probability infection_probability
    for (auto i : susceptible_positions)
    {
        double supsceptible_x = people[i].position.first;
        double supsceptible_y = people[i].position.second;
        for (auto j : infected_positions)
        {
            double infected_x = people[j].position.first;
            double infected_y = people[j].position.second;
            double distance{std::sqrt(std::pow(supsceptible_x - infected_x, 2) + std::pow(supsceptible_y - infected_y, 2))};
            if (distance <= infection_radius)
            {
                double p = probability(re);
                //the probability for p to be smaller than probability_infection is exactly the probability infection
                //since p comes from a uniform distribution from 0 to 1
                if (p <= infection_probability)
                {
                    people[i].infection_status = InfectionStatus::infected;
                    break;
                }
            }
        }
    }
}

// adds +1 to counter_infected for each infected person and to conter_susceptible for each recovered people. Updates the statewhen necessary
void Population::update_status()
{
    for (auto &person : people)
    {
        if (person.infection_status == InfectionStatus::infected)
        {
            if (person.counter_infected < recovery_time)
            {
                person.counter_infected++;
            }
            else
            {
                person.infection_status = InfectionStatus::recovered;
                person.counter_infected = 0;
            }
        }

        else if (person.infection_status == InfectionStatus::recovered)
        {
            if (person.counter_recovered < susceptibility_time)
            {
                person.counter_recovered++;
            }
            else{
                person.infection_status = InfectionStatus::susceptible;
                person.counter_recovered = 0;
            }
        }
    }
}

// returns the vector people, wich represents the current status of the infection
std::vector<Person> Population::get_people()
{
    return people;
}

std::array<int, 3> Population::counts()
{
    std::array<int, 3> counts{0, 0, 0};
    for (const auto &person : people)
    {
        if (person.infection_status == InfectionStatus::susceptible)
        {
            counts[0]++;
        }
        else if (person.infection_status == InfectionStatus::infected)
        {
            counts[1]++;
        }
        else
        {
            counts[2]++;
        }
    }
    return counts;
}