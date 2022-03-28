#include "../include/Simulation.hpp"

#include <array>
#include <fstream>
#include <stdexcept>
#include <string>

#include "../include/Population.hpp"

Simulation::Simulation(std::pair<double, double> bounding_box,
                       double infection_radius, double infection_probability,
                       int num_steps, double step_size, int recovery_time,  int susceptibility_time,
                       int population_size, bool add_meetingpoint, double meetingpoint_probability,
                       std::string file_simulation,
                       std::string file_overview )
    : bounding_box(bounding_box),
      infection_radius(infection_radius),
      infection_probability(infection_probability),
      num_steps(num_steps),
      recovery_time(recovery_time),
      susceptibility_time(susceptibility_time),
      step_size(step_size),
      population_size(population_size),
      population(bounding_box, infection_radius, infection_probability,
                 num_steps, step_size, recovery_time, susceptibility_time, population_size,
                 add_meetingpoint, meetingpoint_probability),
      csv_file_simulation(file_simulation),
      csv_file_overview(file_overview),
      add_meetingpoint(add_meetingpoint),
      meetingpoint_probability(meetingpoint_probability)
{
    // check correctness of the values inserted
    if (bounding_box.first <= 0. or bounding_box.second <= 0.)
    {
        throw std::invalid_argument(
            "The width/height of the bounding_box cannot be negative");
    }
    else if (infection_radius <= 0.)
    {
        throw std::invalid_argument(
            "The infection_radius must be greater than 0");
    }
    else if (infection_probability < 0. or infection_probability > 1.)
    {
        throw std::invalid_argument(
            "The infection_probability must be between 0 and 1");
    }
    else if (num_steps <= 0)
    {
        throw std::invalid_argument("The num_steps must be greater than 0");
    }
    else if (step_size <= 0.)
    {
        throw std::invalid_argument("The step_size must be greater than 0");
    }
    else if (recovery_time <= 0)
    {
        throw std::invalid_argument("The recovery_time must be greater than 0");
    }
    else if (susceptibility_time <= 0)
    {
        throw std::invalid_argument("The susceptibility_time must be greater than 0");
    }
    else if (step_size >
             0.1 * std::min(bounding_box.first, bounding_box.second))
    {
        throw std::invalid_argument(
            "The step_size cannot be bigger than 1/10 * min(width, height) of "
            "the bounding box");
    }
    else if(meetingpoint_probability < 0. or meetingpoint_probability > 1.){
        throw std::invalid_argument(
            "The meetingpoint_probability must be between 0 and 1");
    }
    write_to_csv();
}

Simulation::~Simulation()
{
    csv_file_simulation.close();
    csv_file_overview.close();
}

std::vector<Person> Simulation::get_people() { return population.get_people(); }

void Simulation::next_step()
{
    population.update_positions();
    population.update_infected();
    population.update_status();
    write_to_csv();
}

std::array<double, 3> Simulation::get_overview()
{
    std::array<double, 3> m;
    auto counts = population.counts();
    m[0] = counts[0] / static_cast<double>(population_size);
    m[1] = counts[1] / static_cast<double>(population_size);
    m[2] = counts[2] / static_cast<double>(population_size);
    return m;
}

void Simulation::write_to_csv()
{
    std::vector<Person> people = population.get_people();
    for (auto &person : people)
    {
        csv_file_simulation << person.position.first << "\t"
                            << person.position.second << "\t"
                            << person.infection_status << "\t";
    }
    long pos = csv_file_simulation.tellp();
    csv_file_simulation.seekp(pos - 1);
    csv_file_simulation << "\n";

    std::array<double, 3> overview = get_overview();
    for (int i = 0; i < 3; i++)
    {
        csv_file_overview << overview.at(i) << "\t";
    }
    pos = csv_file_overview.tellp();
    csv_file_overview.seekp(pos - 1);
    csv_file_overview << "\n";
}