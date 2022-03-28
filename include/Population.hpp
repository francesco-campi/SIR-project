#ifndef POPULATION_H
#define POPULATION_H

#include <array>
#include <vector>
#include <random>
#define _USE_MATH_DEFINES
#include "Person.hpp"

class Population
{
private:
    // vector cotaining all the people that compose the population
    std::vector<Person> people;
    // all the parameters of the model
    std::pair<double, double> bounding_box; //respectively width and height
    double infection_radius;
    double infection_probability;
    int num_steps;
    int recovery_time;
    int susceptibility_time;
    double step_size;
    bool add_meetingpoint;
    double meetingpoint_probability;
    int population_size;
    std::pair<double, double> meeting_point; //position of a fixed meeting point (e.g. city center, grocery store)
    std::uniform_real_distribution<double> unif_angle = std::uniform_real_distribution<double>(0, 2. * M_PI);
    std::uniform_real_distribution<double> probability = std::uniform_real_distribution<double>(0., 1.);
    std::uniform_real_distribution<double> unif_width = std::uniform_real_distribution<double>(0, bounding_box.first);
    std::uniform_real_distribution<double> unif_height = std::uniform_real_distribution<double>(0, bounding_box.second);
    std::default_random_engine re;

    /**
     * @brief 
     * 
     */
    void compute_position(Person& person);

public:
    /**
     * @brief Constructs a new Population object, stores the parameters of the
     * model and initializes the people vector with "supsceptible" status and
     * random position. The first person is initialized as infected.
     *
     * @param bounding_box size of the environment
     * @param infection_radius distance within which the infection can occur
     * @param infection_probability probability of infection after coming in contact with an infected person
     * @param num_steps total number of iterations
     * @param step_size fixed length of each step for the movement of the people in the environment
     * @param recovery_time time after which a person recovers
     * @param susceptibility_time time after which a person becomes susceptible again
     * @param population_size number of people in the population
     * @param add_meetingpoint boolean value, if there should be a meetingpoint in the center
     * @param meetingpoint_probability probability of people going to the meetingpoint in the center
     */
    Population(std::pair<double, double> bounding_box, double infection_radius,
               double infection_probability, int num_steps, double step_size, int recovery_time, int susceptibility_time,
                int population_size, bool add_meetingpoint, double meetingpoint_probability);
    /**
     * @brief changes the positions of each person by a step of fixed length and random direction and deals with the box dimension
     *
     */
    void update_positions();
    /**
     * @brief checks for neighbours of the infected people and changes the status with probability infection_probability
     *
     */
    void update_infected();
    /**
     * @brief updates the state of the infected and recovered people
     *
     */
    void update_status();
    /**
     * @brief returns the vector people, wich represents the current status of the infection
     *
     */
    std::vector<Person> get_people();
    /**
     * @brief returns the number of supsceptible, infected and recovered people 
     * 
     * @return std::array<int, 3> 
     */
    std::array<int, 3> counts();
};

#endif