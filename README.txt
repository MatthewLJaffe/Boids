This project is a boid ecosystem created by Matthew Jaffe
This code was written Febuary 2nd-6th 2023 

All relevant code files are included in the same directory in this directory. Dependencies are included
in the src directory, and required assets such as the ttf font and pngs are included in the assets directory
All dependcies are locally included in this directory and set up to correctly link in the project. 

To compile and run the program open the solution in Visual Studio, select x64 as the target platform,
and then the program can be run in visual studio

This boid ecosystem contains 3 different types of prey boids as well as predator boids. Prey boids will 
try to flock together with boids of the same color, and collect food while avoiding prey as well as the black circles.

Predator boids will hunt prey boids and do not flock with other predators.

The following traits are configurable at runtime

For Prey
Seperation: Determines how focused boids will be at keeping some distance from eachother
Alignment: Makes neighboring boids within a flock try to point in the same direction
Cohesion: Makes boids try to swim to the center of all flock mates visible to them
Speed: How fast the boids move
Acceleration: How fast the boids turn
Food attraction: Makes boids prioritize swimiming towards food
Predator avoidance: Makes boids prioritize swimming away from predators
Field of view: controls the maximum angle around a boid that it can see
Vision radius: determines how far away a boid can see

For Predators
Aggression: How focused predator boids are on eating prey
Speed: How fast the boids move
Acceleration: How fast the boids turn
Starvation time: The time in seconds a predator takes to die without eating
Food to reproduce: the amount of prey boids a predator must eat to reproduce
Field of view: controls the maximum angle around a boid that it can see
Vision radius: determines how far away a boid can see

For Prey Food
Spawn rate: how fast food spawns
Food to reproduce: how much food a prey boid must eat to reproduced