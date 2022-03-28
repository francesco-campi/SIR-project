#include <array>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <sstream>

#include "include/Population.hpp"
#include "include/Simulation.hpp"

int main()
{
    std::ifstream input("../INPUT.txt"); //The input file
    std::map<std::string, std::string> configs;

    while (input)
    {
        std::string key;
        std::string value;
        std::getline(input, key, ':');    //Read up to the : delimiter into key
        std::getline(input, value, '\n'); //Read up to the newline into value
        configs[key] = value;
    }
    input.close();

    //extract the model parameters
    std::pair<double, double> bounding_box(
        std::stod(configs.at("bounding_box_width")), std::stod(configs.at("bounding_box_height"))); // respectively width and height
    double infection_radius{std::stod(configs.at("infection_radius"))};
    double infection_probability{std::stod(configs.at("infection_probability"))};
    int num_steps{std::stoi(configs.at("num_steps"))};
    double step_size{std::stod(configs.at("step_size"))};
    int recovery_time{std::stoi(configs.at("recovery_time"))}; // number of steps
    int susceptibility_time{std::stoi(configs.at("susceptibility_time"))}; 
    int population_size{std::stoi(configs.at("population_size"))};
    bool add_meetingpoint{configs.at("add_meetingpoint") == "true"};
    double meetingpoint_probability{std::stod(configs.at("meetingpoint_probability"))};

    std::unique_ptr<Simulation> simulation;
    try{
        simulation = std::make_unique<Simulation>(bounding_box,
    infection_radius, infection_probability, num_steps, step_size,
    recovery_time,susceptibility_time, population_size, add_meetingpoint,
    meetingpoint_probability);
    }
    catch (const std::invalid_argument & error){
            std::cout << "Warning : " << error.what() << std::endl;
        }

    std::vector<std::array<double, 3>> overviews;
    std::cout << "Start of the simulation\n";
    // beginning of the simulation
    for (auto iter = 1; iter <= num_steps; iter++)
    {
        simulation->next_step();
        auto overview = simulation->get_overview();
        overviews.push_back(overview);
        std::cout << "\nTime stamp = " << iter << std::endl;
        std::cout << "Susceptible = " << overview[0]
                  << "\nInfected = " << overview[1]
                  << "\nRecovered = " << overview[2] << std::endl;
    }

    return 0;
}