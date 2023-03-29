# Project: Simulate the spread of an epidemic

## General project description
The goal of this project is to implement at least one model to simulate and visualize the spread of an epidemic. Later on we will try to fit the model(s) to the current COVID-19 epidemic. The idea is to gradually increase the sophistication of the simulation by adding more assumptions and conditions, e.g. more complex behaviors of the people (people living in households, going to work, grocery store, separated communities, quarantine). Additionally, we might switch to to a modified SIR model to include different assumptions about the epidemic itself, e.g. a latent period of the disease where the person is not infectious. In the end, a visualization of the simulated data is planned. This probably will be done by exporting data and handling it in python. Alternatively, we might implement a live GUI where the user can choose the modeling parameters.

A few sources:

- Description of the method: [Modeling Coronavirus part I - the SIR model](https://www.davidketcheson.info/2020/03/17/SIR_model.html)
- A working example: [Epidemic Simulation](https://prajwalsouza.github.io/Experiments/Epidemic-Simulation.html)
- A paper to read: [The Mathematics of InfectiousDiseases, Herbert W. Hethcote, SIAM Review](https://epubs.siam.org/doi/pdf/10.1137/S0036144500371907) (very in-depth)

## How to run the simulation
Run the following commands:<br />
cmake -B build<br />
cd build<br />
make<br />
./sir<br />
## Change parameters
Please input the parameters into the **INPUT.txt** file.  <br />

## Output
The results of the simulation will be safed in the **tests** folder. <br />

### Simulation.csv: 
Here you find the position and status of each person for all timesteps. <br />
 <br />
ith Line = ith Person <br />
jth column = jth timestep <br />
 <br />
Each entry has the format  <br />
**Position_x	Position_y	Status** <br />
for the corresponding person and timestep. <br />
 <br />
### Overview.csv: 
Here you find an overview of the proportions of the population that are suceptible, recoverd and infected per timestep. <br />
 <br />
ith Line = ith timestep <br />
 <br />
Each entry has the format  <br />
**suceptible	infected	recovered** <br />

## Visualization
In the **visualization** folder you can find a jupyter notebook to visualize the output. <br />
After running the notebook four files will be safed in the **visualization** folder. <br />
