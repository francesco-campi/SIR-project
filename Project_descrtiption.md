# Project: Simulate the spread of an epidemic

Idea contributed by Kai Nierula <kai.nierula@tum.de> and Adrian Stobbe <adrian.stobbe@tum.de>.

## General project description

The goal of this project is to implement at least one model to simulate and
visualize the spread of an epidemic. Later on we will try to fit the model(s) to
the current COVID-19 epidemic.
The idea is to gradually increase the sophistication of the simulation by
adding more assumptions and conditions, e.g. more complex behaviors of the
people (people living in households, going to work, grocery store, separated
communities, quarantine). Additionally, we might switch to to a modified SIR
model to include different assumptions about the epidemic itself, e.g. a latent
period of the disease where the person is not infectious.
In the end, a visualization of the simulated data is planned. This probably
will be done by exporting data and handling it in python. Alternatively, we
might implement a live GUI where the user can choose the modeling parameters.

A few sources:
- Description of the method: [Modeling Coronavirus part I - the SIR model](https://www.davidketcheson.info/2020/03/17/SIR_model.html)
- A working example: [Epidemic Simulation](https://prajwalsouza.github.io/Experiments/Epidemic-Simulation.html)
- A paper to read: [The Mathematics of InfectiousDiseases, Herbert W. Hethcote, SIAM Review](https://epubs.siam.org/doi/pdf/10.1137/S0036144500371907) (very in-depth)


## Sprint 1
In the first sprint, the population will be initialized, walking randomly within a given premise. If feasable within the time frame, the first SRI model will already be implemented. Infected people will transmit the disease to other people with a specific probability if the susceptible people are within a radius of the infected. After a given time period, the infected people will recover and no longer will be able to catch or transmit the disease.

### Definion of "done"
- User will be able to input:
    - number of people
    - Length of the sides of the box
    - probability of spreading the infection
    - infection radius
    - number of timesteps that should be calculated

- Output will be:
    - Position (x,y) of each person within the box 
    - Status of each person (suceptible,recoverd,infected) as (0,1,2) (if we are able to do that in Sprint 1)



## Sprint 2
The first simple SRI model will be implemented/finished. Additional variants will also be implemented, ideas for these are the following:
- people going to fixed meeting point (e.g. city center, grocery store) 
- people going into quarantine if infectious people can be found
- people living in different communities, where a person needs to travel from one box to another in order to be able to infect another community
- people getting infected a second time 
- existence of a latent period of the disease where the person is not infectious 



### Definition of "done"
- The simple SRI model works and outputs the satus of each person (see Sprint 1)
- The output is saved into a file which name the user can choose
- At least two modified versions of the SIR are implemented


## Sprint 3
In this sprint, the code performance will be evaluated and improved. Potential performance bottlenecks will be found (e.g. using a profiler such as gprof) and optimization options for the code will be implemented. This investigation will be based on topics covered in the lecture. Optionally, a way of visualizing the epidemic will be created, either trough exporting the data into python or using a GUI in C++.

### Definition of "done"
- A file `performance.md` presents the observations from the performance analysis (at least two different scenarios)
- The same file presents at least one different optimization techniques you applied, with the observable performance effects
- Some form of visualization
