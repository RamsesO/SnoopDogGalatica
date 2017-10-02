# Snoop Dogg Galatica
The dankest universe that no one has ever seen.

## Warbird Simulation Overview

### Ruber System

* Planets and Objects
    * Sun (Ruber)
    * Planet #1 (Unum)
        * Missile Site #1
    * Planet #2 (Duo)
        * Moon #1
        * Moon #2 (Secundus)
            * Missile Site #2
    * Spaceship

* Animation
    * Sun in the center
    * Unum and Duo rotate around the Sun on the XZ axis
        * x-axis = length
        * y-axis = height
        * z-axis = depth
    * The moons orbit Duo at the XZ axis
    * Use the fixed interval timer's Time Quantum (TQ) to call an update function for each "simulation update frame" to “update” the planet and moon orbits.
    * There are two different TQ
        * 5 milliseconds (fast)
        * 40 milliseconds (ace)
            * 25 updates per seconds
            * Unum should rotate every 8 seconds around Ruber

* Cameras


## Phase #1