# SIR-project
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
