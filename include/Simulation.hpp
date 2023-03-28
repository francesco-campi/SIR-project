#ifndef SIMULATION_H
#define SIMULATION_H

#include <array>
#include <memory>
#include <fstream>
#include <string>

#include "InfectionStatus.hpp"
#include "Person.hpp"
#include "Population.hpp"

class Simulation
{
private:
    // first parameter is the width and second parameter is the height of the bounding Box positioned at (0,0)
    std::pair<double, double> bounding_box;
    double infection_radius;
    double infection_probability; // respectively width and height
    int num_steps;
    double step_size;
    int recovery_time; // number of steps
    int susceptibility_time;
    int population_size;
    bool add_meetingpoint;
    double meetingpoint_probability;
    Population population;

    std::ofstream csv_file_simulation;
    std::ofstream csv_file_overview;

public:
    /**
     * @brief Constructor function: stores and checks the parameters of the model. 
     * The values for the bounding_box, infection_radius, infection_probability, num_steps,
     * step_size and recovery_time need to be positive. Furthermore
     * infection_probability needs to be between 0 and 1 and the step_size
     * cannot be bigger than 1/10 * min(width, height) of the bounding box.
     *
     * @param bounding_box size of the environment
     * @param infection_radius distance within which the infecton can occur
     * @param infection_probability probability of infection after coming in contact with an infected person
     * @param num_steps total number of iterations
     * @param step_size fixed length of each step for the movement of the people in the environment
     * @param recovery_time time after which a person recovers
     * @param susceptibility_time time after which a person becomes susceptible again
     * @param population_size number of people in the population
     * @param add_meetingpoint boolean value, if there should be a meetingpoint in the center
     * @param meetingpoint_probability probability of people going to the meetingpoint in the center
     * @param file_simulation a file path for the output of the simulation
     * @param file_overview a file path for the output of an overview
     */
    Simulation(std::pair<double, double> bounding_box, double infection_radius,
               double infection_probability, int num_steps, double step_size,
               int recovery_time,  int susceptibility_time, int population_size,
               bool add_meetingpoint, double meetingpoint_probability,
               std::string file_simulation = "../data/simulation.csv",
               std::string file_overview = "../data/overview.csv");

    ~Simulation();

    /**
     * @brief Get the vector of people containing all information about the simulation
     *
     * @return std::vector<Person>
     */
    std::vector<Person> get_people();

    /**
     * @brief performs the next step of the simulation
     *
     */
    void next_step();

    /**
     * @brief Get on overview of the simulation (lighter than the whole vector of people)
     *
     * @return std::array<double, 3> At position 0 is the porportion of suceptible, at position 1 
     * is the porportion of infected and at position 2 is the porportion of recovered.
     */
    std::array<double, 3> get_overview();

    /**
     * @brief Writes the output of the current timestep into two csv files.
     * 
     */
    void write_to_csv();
};

#endif
